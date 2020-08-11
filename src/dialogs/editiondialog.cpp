/* - DownZemAll! - Copyright (C) 2019-present Sebastien Vavassori
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

#include "editiondialog.h"
#include "ui_editiondialog.h"

#include <Globals>
#include <Core/DownloadItem>
#include <Core/IDownloadItem>
#include <Core/ResourceItem>
#include <Widgets/TextEditorWidget>

#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtGui/QCloseEvent>
#include <QtGui/QTextBlock>
#include <QtWidgets/QTextEdit>

#define C_DEFAULT_WIDTH     700
#define C_DEFAULT_HEIGHT    500


EditionDialog::EditionDialog(const QList<IDownloadItem*> &items, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditionDialog)
    , m_items(items)
{
    ui->setupUi(this);

    setWindowTitle(QString("%0 - %1").arg(STR_APPLICATION_NAME).arg(tr("Smart Edit")));

    connect(ui->editor, SIGNAL(textChanged()), this, SLOT(onTextChanged()));

    ui->subtitleLabel->setText(tr("%0 selected files to edit").arg(m_items.count()));
    ui->warningLabel->setVisible(false);


    ui->editor->clear();
    foreach (auto item, items) {
        const DownloadItem *downloadItem = static_cast<const DownloadItem*>(item);
        if (downloadItem) {
            const ResourceItem *resource = downloadItem->resource();
            ui->editor->append(resource->url());
        }
    }
    ui->editor->setModified(false);

    readSettings();
}

EditionDialog::~EditionDialog()
{
    delete ui;
}

void EditionDialog::closeEvent(QCloseEvent *)
{
    writeSettings();
}

/******************************************************************************
 ******************************************************************************/
void EditionDialog::accept()
{
    writeSettings();
    if (ui->editor->isModified()) {
        const int itemCount = m_items.count();
        const int lineCount = ui->editor->count();
        if (itemCount != lineCount) {
            return; // Cancel action
        }
        applyChanges();
    }
    QDialog::accept();
}

/******************************************************************************
 ******************************************************************************/
void EditionDialog::onTextChanged()
{
    const int itemCount = m_items.count();
    const int lineCount = ui->editor->count();

    ui->buttonBox->setEnabled(lineCount == itemCount);
    ui->warningLabel->setVisible(lineCount != itemCount);
    ui->warningLabel->setText(
                tr("Warning: number of lines is <%0> but should be <%1>!")
                .arg(lineCount).arg(itemCount));
}

/******************************************************************************
 ******************************************************************************/
void EditionDialog::applyChanges()
{
    const int itemCount = m_items.count();
    const int lineCount = ui->editor->count();
    Q_ASSERT(itemCount == lineCount);
    for (int index = 0; index < itemCount; ++index) {

        auto item = m_items.at(index);
        DownloadItem *downloadItem = static_cast<DownloadItem*>(item);
        ResourceItem *resource = downloadItem->resource();
        auto oldUrl = resource->url();

        auto text = ui->editor->at(index);
        auto newUrl = text.simplified();

        if (newUrl != oldUrl) {
            resource->setUrl(newUrl);
            downloadItem->stop();
            downloadItem->pause();
        }
    }
}

/******************************************************************************
 ******************************************************************************/
void EditionDialog::readSettings()
{
    QSettings settings;
    settings.beginGroup("EditionDialog");
    const QSize defaultSize(C_DEFAULT_WIDTH, C_DEFAULT_HEIGHT);
    resize(settings.value("DialogSize", defaultSize).toSize());
    settings.endGroup();
}

void EditionDialog::writeSettings()
{
    QSettings settings;
    settings.beginGroup("EditionDialog");
    settings.setValue("DialogSize", size());
    settings.endGroup();
}
