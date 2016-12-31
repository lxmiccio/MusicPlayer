#ifndef STACKEDWIDGET_H
#define STACKEDWIDGET_H

#include <QMainWindow>
#include <QStackedWidget>

class StackedWidget : public QMainWindow
{
  Q_OBJECT

  public:
    explicit StackedWidget(QWidget* parent = 0);
    QStackedWidget* stackedWidget();

  public slots:
    void previousView();

  private:
    QStackedWidget* m_stackedWidget;
};

#endif // STACKEDWIDGET_H
