#ifndef RESWINDOW_H
#define RESWINDOW_H

#include <QDialog>
#include <QTreeWidget>
#include "lrparser.h"
#include <QLayout>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class ResWindow;
}

class ResWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ResWindow(QObject* appmanager, QWidget *parent = nullptr);
    ~ResWindow();

    QTreeWidgetItem* AddRoot(QString name, bool Meta);
    QTreeWidgetItem* AddChild(QTreeWidgetItem *parent,QString , bool , Token );

    void SetResTrees(QVector<Node*>);
    void BuildTree(Node*);
    void AddAllChildren(QTreeWidgetItem* par,Node*);
    void reject() override;

signals:
    void Closed();

public slots:
    void Next();
    void Prev();

private:
    Ui::ResWindow *ui;

    QObject* _appManager;

    QVector<Node*> _resTrees;
    int _index;
    QTreeWidget *_treeContainer;
    QLabel *_indLabel;
    QLabel *_res;
    QLabel *_resNo;

    QPushButton *_next;
    QPushButton *_prev;
};

#endif // RESWINDOW_H
