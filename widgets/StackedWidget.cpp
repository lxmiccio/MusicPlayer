#include "StackedWidget.h"

#include "MainWindow.h"

StackedWidget::StackedWidget(QWidget *parent) : QMainWindow(parent)
{
  m_stackedWidget = new QStackedWidget();
  setCentralWidget(m_stackedWidget);

  MainWindow* mainWindows = new MainWindow(this);
  m_stackedWidget->addWidget(mainWindows);
}

QStackedWidget* StackedWidget::stackedWidget()
{
  return m_stackedWidget;
}

void StackedWidget::previousView()
{
  QString currentClassName = m_stackedWidget->currentWidget()->metaObject()->className();

  for(int i = m_stackedWidget->count() - 1; i >= 0; --i) {
    QWidget* widget = m_stackedWidget->widget(i);

    if(widget->metaObject()->className() == currentClassName) {
      m_stackedWidget->removeWidget(widget);
      delete widget;
    } else {
      m_stackedWidget->setCurrentWidget(m_stackedWidget->widget(i));
      break;
    }
  }
}
