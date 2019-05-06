#pragma once

#include <qtreewidget.h>
#include <scene/scene_node.h>

class TreeWidget : public QTreeWidget {
Q_OBJECT

public:
    TreeWidget(QWidget* parent = nullptr);

public slots:
    void showSceneNode(SceneNode* node);

private slots:
    void itemClickSlot(QTreeWidgetItem* item);

signals:
    void nodeProperty(const QString& value);

private:
    QTreeWidgetItem* AddNodeToItem(SceneNode* node);

};