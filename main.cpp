#include <QApplication>
#include <QDateTime>
#include <QFileInfo>
#include <QFontDatabase>

#include "MainWindow.h"
#include "Track.h"

#define ENABLE_DEBUG

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();

    QString filepath = context.file;
    QString filename = filepath.mid(filepath.lastIndexOf("/") + 1);

    QString shortenedFunction = context.function;
    shortenedFunction = shortenedFunction.mid(shortenedFunction.indexOf("::") + 2);

    switch (type)
    {
    case QtDebugMsg:
#ifdef ENABLE_DEBUG
        fprintf(stderr, "%s:%u, %s ---> %s\n", filename.toUtf8().constData(), context.line, shortenedFunction.toUtf8().constData(), localMsg.constData());
#endif
#ifdef WRITE_LOG
        static QString logFile;
        static QFile file;

        if(logFile.length() == 0)
        {
            logFile = "log_" + QDateTime::currentDateTime().toString() + ".txt";
            file = QFile(logFile);
            file.open(QIODevice::WriteOnly);
        }

        if(file.isOpen())
        {
            file.write(QString(filename + ":" + context.line + ", " + shortenedFunction + " ---> " + localMsg);
        }
#endif
        break;
    case QtInfoMsg:
    case QtWarningMsg:
    case QtCriticalMsg:
        fprintf(stderr, "%s\n", localMsg.constData());
        break;
    case QtFatalMsg:
        fprintf(stderr, "%s\n", localMsg.constData());
        abort();
    }
}

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    qInstallMessageHandler(myMessageOutput);
    qRegisterMetaType<QFileInfo>("QFileInfo");
    qRegisterMetaType<Track*>("Track");

    QFontDatabase::addApplicationFont(":/fonts/sniglet-regular.ttf");
    QFont font = QApplication::font();
    font.setFamily("Sniglet");
    font.setPointSize(9);
    font.setStyleStrategy(QFont::PreferAntialias);
    QApplication::setFont(font);

    qsrand(QDateTime::currentDateTime().toTime_t());

    MainWindow* mainWindow = MainWindow::instance();
    mainWindow->showMaximized();

    return application.exec();

    /* TODO here
     */
}
