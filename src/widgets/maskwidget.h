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

#ifndef WIDGETS_MASK_WIDGET_H
#define WIDGETS_MASK_WIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class MaskWidget;
}

class MaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MaskWidget(QWidget *parent);
    ~MaskWidget();

    QString currentMask() const;
    void setCurrentMask(const QString &currentMask);

    bool colorizeErrors() const;
    void setColorizeErrors(bool enabled);

signals:
    void currentMaskChanged(QString mask);

private slots:
    void onCurrentTextChanged(const QString &text);

private:
    Ui::MaskWidget *ui;
    bool m_colorizeErrorsEnabled;

    inline void colorizeErrors(const QString &text);
};

#endif // WIDGETS_MASK_WIDGET_H