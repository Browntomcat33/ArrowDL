/* - DownZemAll! - Copyright (C) 2019 Sebastien Vavassori
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; If not, see <http://www.gnu.org/licenses/>.
 */

#include "filterwidget.h"
#include "ui_filterwidget.h"

#include <QtCore/QtMath>
#include <QtWidgets/QCheckBox>
#ifdef QT_DEBUG
#  include <QtCore/QDebug>
#endif

static uint encode(const QList<QCheckBox*> checkboxes)
{
    uint code = 0;
    for (int i = 0; i < checkboxes.count(); ++i) {
        const QCheckBox *checkBox = checkboxes.at(i);
        if (checkBox->isChecked()) {
            code |= (1 << i);
        }
    }
    return code;
}

static void decode(const uint code, QList<QCheckBox*> checkboxes)
{
    for (int i = 0; i < checkboxes.count(); ++i) {
        QCheckBox *checkBox = checkboxes.at(i);
        checkBox->setChecked(code & (1 << i));
    }
}

FilterWidget::FilterWidget(QWidget *parent) : QWidget(parent)
  , ui(new Ui::FilterWidget)
{
    ui->setupUi(this);

    clearFilters();

    connect(ui->fastFilteringOnlyCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onFilterChanged(int)));
    connect(ui->fastFilteringComboBox, SIGNAL(currentTextChanged(QString)),
            this, SLOT(onFilterChanged(QString)));
}

FilterWidget::~FilterWidget()
{
    delete ui;
}

/******************************************************************************
 ******************************************************************************/
/*!
 * Returns an integer representing the current state of all the QCheckBox
 * in the widget.
 *
 * It's a convenient method for (re)storing the QCheckBox's widget settings.
 *
 */
uint FilterWidget::state() const
{
    return encode(allCheckBoxes());
}

/*!
 * Sets the state of all the QCheckBox in the widget.
 *
 * It's a convenient method for (re)storing the QCheckBox's widget settings.
 *
 */
void FilterWidget::setState(uint code)
{
    decode(code, allCheckBoxes());
}

inline QList<QCheckBox*> FilterWidget::allCheckBoxes() const
{
    QList<QCheckBox*> checkboxes = ui->checkBoxGroup->findChildren<QCheckBox*>();
    checkboxes.prepend(ui->fastFilteringOnlyCheckBox);
    return checkboxes;
}

/******************************************************************************
 ******************************************************************************/
QString FilterWidget::text() const
{
    return ui->fastFilteringComboBox->currentText();
}

void FilterWidget::setText(const QString &text)
{
    if (ui->fastFilteringComboBox->currentText() != text) {
        ui->fastFilteringComboBox->setCurrentText(text);
    }
}

/******************************************************************************
 ******************************************************************************/
void FilterWidget::onFilterChanged(int)
{
    emit regexChanged(regex());
}

void FilterWidget::onFilterChanged(const QString &)
{
    emit regexChanged(regex());
}

/******************************************************************************
 ******************************************************************************/
void FilterWidget::clearFilters()
{
    const QList<QCheckBox*> checkboxes = ui->checkBoxGroup->findChildren<QCheckBox*>();
    foreach (auto checkbox, checkboxes) {
        ui->checkBoxGroup->layout()->removeWidget(checkbox);
        checkbox->setParent(0);
        delete checkbox;
    }
}

void FilterWidget::addFilter(const QString &title, const QString &regexp)
{
    const QList<QCheckBox*> checkboxes = ui->checkBoxGroup->findChildren<QCheckBox*>();
    const int count = checkboxes.count();
    const std::div_t dv = std::div(count, 3);
    const int row = dv.quot;
    const int column = dv.rem;

    QCheckBox *checkbox = new QCheckBox(title, ui->checkBoxGroup);
    checkbox->setToolTip(QString("%0\n%1").arg(title).arg(regexp));
    checkbox->setProperty("regexp", regexp);

    connect(checkbox, SIGNAL(stateChanged(int)), this, SLOT(onFilterChanged(int)));

    QGridLayout *layout = (QGridLayout*) ui->checkBoxGroup->layout();
    layout->addWidget(checkbox, row, column);
}

/******************************************************************************
 ******************************************************************************/
QRegExp FilterWidget::regex() const
{
    ui->fastFilteringComboBox->setStyleSheet(QString());
    QString filter;

    const QString text = ui->fastFilteringComboBox->currentText();
    if (!text.isEmpty()) {
        filter += "(" + text + ")";

        QRegExp regexTest(filter);
        if (!regexTest.isValid()) {
            ui->fastFilteringComboBox->setStyleSheet(QLatin1String("color: rgb(255, 0, 0);"));
        }
    }

    if (!ui->fastFilteringOnlyCheckBox->isChecked()) {
        QStringList parts;
        const QList<QCheckBox*> checkboxes = ui->checkBoxGroup->findChildren<QCheckBox*>();
        foreach (auto checkbox, checkboxes) {
            if (checkbox->isChecked()) {
                parts << checkbox->property("regexp").toString();
            }
        }
        if (!parts.isEmpty()) {
            if (!filter.isEmpty()) {
                filter += "|";
            }
            foreach (auto part, parts) {
                filter += "(";
                filter += part;
                filter += ")|";
            }
            if (filter.endsWith('|')) {
                filter.chop(1);
            }
        }
    }
    QRegExp regex(filter);
    regex.setPatternSyntax(QRegExp::RegExp);
    return regex;
}