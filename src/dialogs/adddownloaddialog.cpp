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

#include "adddownloaddialog.h"
#include "ui_adddownloaddialog.h"

#include <Core/DownloadManager>
#include <Core/Regex>
#include <Core/ResourceItem>

#include <QtCore/QList>
#include <QtCore/QSettings>
#include <QtCore/QUrl>
#include <QtGui/QCloseEvent>
#include <QtWidgets/QAction>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMessageBox>
#ifdef QT_DEBUG
#  include <QtCore/QDebug>
#endif


AddDownloadDialog::AddDownloadDialog(const QUrl &url, DownloadManager *downloadManager, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddDownloadDialog)
    , m_downloadManager(downloadManager)

{
    ui->setupUi(this);

    ui->pathWidget->setPathType(PathWidget::Directory);

    ui->downloadLineEdit->setText(url.toString());
    ui->downloadLineEdit->setFocus();
    ui->downloadLineEdit->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->downloadLineEdit, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));

    connect(ui->downloadLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onChanged(QString)));
    connect(ui->pathWidget, SIGNAL(currentPathChanged(QString)), this, SLOT(onChanged(QString)));
    connect(ui->maskWidget, SIGNAL(currentMaskChanged(QString)), this, SLOT(onChanged(QString)));

    readSettings();
}

AddDownloadDialog::~AddDownloadDialog()
{
    delete ui;
}

/******************************************************************************
 ******************************************************************************/
void AddDownloadDialog::accept()
{
    doAccept(true);
}

void AddDownloadDialog::acceptPaused()
{
    doAccept(false);
}

void AddDownloadDialog::reject()
{
    QDialog::reject();
}

/******************************************************************************
 ******************************************************************************/
void AddDownloadDialog::showContextMenu(const QPoint &/*pos*/)
{
    QMenu *contextMenu = ui->downloadLineEdit->createStandardContextMenu();
    QAction *first = contextMenu->actions().first();

    QAction action_1_to_10(tr("Insert [ 1 -> 10 ]"), contextMenu);
    QAction action_1_to_100(tr("Insert [ 1 -> 100 ]"), contextMenu);
    QAction action_01_to_10(tr("Insert [ 01 -> 10 ]"), contextMenu);
    QAction action_001_to_100(tr("Insert [ 001 -> 100 ]"), contextMenu);

    connect(&action_1_to_10, SIGNAL(triggered()), this, SLOT(insert_1_to_10()));
    connect(&action_1_to_100, SIGNAL(triggered()), this, SLOT(insert_1_to_100()));
    connect(&action_01_to_10, SIGNAL(triggered()), this, SLOT(insert_01_to_10()));
    connect(&action_001_to_100, SIGNAL(triggered()), this, SLOT(insert_001_to_100()));

    contextMenu->insertAction(first, &action_1_to_10);
    contextMenu->insertAction(first, &action_1_to_100);
    contextMenu->insertAction(first, &action_01_to_10);
    contextMenu->insertAction(first, &action_001_to_100);
    contextMenu->insertSeparator(first);

    contextMenu->exec(QCursor::pos());
    contextMenu->deleteLater();
}

void AddDownloadDialog::insert_1_to_10()
{
    ui->downloadLineEdit->insert("[1:10]");
}

void AddDownloadDialog::insert_01_to_10()
{
    ui->downloadLineEdit->insert("[01:10]");
}

void AddDownloadDialog::insert_1_to_100()
{
    ui->downloadLineEdit->insert("[1:100]");
}

void AddDownloadDialog::insert_001_to_100()
{
    ui->downloadLineEdit->insert("[001:100]");
}

/******************************************************************************
 ******************************************************************************/
void AddDownloadDialog::onChanged(QString)
{
    const bool enabled =
            !ui->downloadLineEdit->text().isEmpty() &&
            !ui->pathWidget->currentPath().isEmpty() &&
            !ui->maskWidget->currentMask().isEmpty();
    ui->startButton->setEnabled(enabled);
    ui->addPausedButton->setEnabled(enabled);
}

/******************************************************************************
 ******************************************************************************/
void AddDownloadDialog::doAccept(const bool started)
{
    const QUrl url(ui->downloadLineEdit->text());

    // Remove trailing / and \ and .
    const QString adjusted = url.adjusted(QUrl::StripTrailingSlash).toString();

    if (Regex::hasBatchDescriptors(adjusted)) {
        const QList<ResourceItem*> items = createItems();
        QMessageBox msgBox(this);
        msgBox.setModal(true);
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setWindowTitle(tr("Download Batch"));
        msgBox.setText(tr("It seems that you are using some batch descriptors."));
        msgBox.setInformativeText(
                    tr("Do you really want to start %0 downloads?\n"
                       "\n"
                       "%1\n"
                       "...\n"
                       "%2")
                    .arg(items.count())
                    .arg(items.first()->url())
                    .arg(items.last()->url()));

        QPushButton *batchButton = msgBox.addButton(tr("Download Batch"), QMessageBox::ActionRole);
        QPushButton *singleButton = msgBox.addButton(tr("Single Download"), QMessageBox::ActionRole);
        QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);

        msgBox.exec();

        if (msgBox.clickedButton() == batchButton) {
            m_downloadManager->append(items, started);
            QDialog::accept();

        } else if (msgBox.clickedButton() == singleButton) {
            m_downloadManager->append(createItem(adjusted), started);
            QDialog::accept();

        } else if (msgBox.clickedButton() == cancelButton) {
            return;
        }

    } else {
        m_downloadManager->append(createItem(adjusted), started);
        QDialog::accept();
    }
    writeSettings();
}

const QList<ResourceItem*> AddDownloadDialog::createItems()
{
    QList<ResourceItem*> list;
    const QString text = ui->downloadLineEdit->text();
    const QStringList urls = Regex::interpret(text);
    foreach (auto url, urls) {
        list << createItem(url);
    }
    return list;
}

ResourceItem* AddDownloadDialog::createItem(const QString &url)
{
    ResourceItem *item = new ResourceItem();
    item->setUrl(url);
    item->setCustomFileName(ui->filenameLineEdit->text());
    item->setReferringPage(ui->referrerLineEdit->text());
    item->setDescription(ui->descriptionLineEdit->text());
    item->setDestination(ui->pathWidget->currentPath());
    item->setMask(ui->maskWidget->currentMask());
    item->setCheckSum(ui->hashLineEdit->text());
    return item;
}

/******************************************************************************
 ******************************************************************************/
void AddDownloadDialog::readSettings()
{
    QSettings settings;
    settings.beginGroup("Wizard");
    ui->pathWidget->setCurrentPath(settings.value("Path", QString()).toString());
    ui->pathWidget->setPathHistory(settings.value("PathHistory").toStringList());
    ui->maskWidget->setCurrentMask(settings.value("Mask", QString()).toString());
    settings.endGroup();
}

void AddDownloadDialog::writeSettings()
{
    QSettings settings;
    settings.beginGroup("Wizard");
    settings.setValue("Path", ui->pathWidget->currentPath());
    settings.setValue("PathHistory", ui->pathWidget->pathHistory());
    settings.setValue("Mask", ui->maskWidget->currentMask());
    settings.endGroup();
}
