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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QFileInfo>
#include <QtWidgets/QMainWindow>

class DownloadItem;
class DownloadManager;
class Settings;

class QLabel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();


    bool saveFile(const QString &path);
    bool loadFile(const QString &path);

protected:
    virtual void closeEvent(QCloseEvent *event);

public slots:

    // File
    void openWizard();
    void openWizard(const QUrl &url);
    void importFromFile();
    void exportSelectedToFile();

    // Edit
    void selectAll();
    void selectNone();
    void invertSelection();
    void selectCompleted();
    void manageMirrors();
    void oneMoreSegment();
    void oneFewerSegment();

    // View
    void showInformation();
    void openFile();
    void openFile(DownloadItem *downloadItem);
    void renameFile();
    void deleteFile();
    void openDirectory();
    void cleanGoneFiles();
    void removeAll();
    void removeCompletedDownloads();
    void removeDownloads();
    void removeSelected();
    void removeDuplicates();
    void removeFailed();
    void removePaused();

    // Download
    void add();
    void resume();
    void cancel();
    void pause();
    void up();
    void top();
    void down();
    void bottom();

    // Options
    void speedLimit();
    void addDomainSpecificLimit();
    void forceStart();
    void showPreferences();

    // Help
    void about();

private slots:
    void onJobAddedOrRemoved(DownloadItem *downloadItem);
    void onJobStateChanged(DownloadItem *downloadItem);
    void onSelectionChanged();

private:
    Ui::MainWindow *ui;
    DownloadManager *m_downloadManager;
    Settings *m_settings;
    QLabel *m_statusBarLabel;

    QFileInfo m_currentFile;

    void readSettings();
    void writeSettings();

    void createActions();
    void createContextMenu();
    void createStatusbar();

    void refreshTitleAndStatus();
    void refreshMenus();

    bool m_showMessageBox;
    inline bool askConfirmation(const QString &text);

    inline QUrl urlFromClipboard() const;

    QString askSaveFileName(const QString &fileFilter, const QString &title = tr("Save As"));
    QString askOpenFileName(const QString &fileFilter, const QString &title = tr("Open"));
};

#endif // MAINWINDOW_H