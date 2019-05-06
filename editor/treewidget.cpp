#include "treewidget.h"
#include <cstdio>

TreeWidget::TreeWidget(QWidget* parent) : QTreeWidget(parent)
{
    QObject::connect(this, &TreeWidget::itemClicked, this, &TreeWidget::itemClickSlot);
}

void TreeWidget::showSceneNode(SceneNode* node)
{
    this->clear();

    QTreeWidgetItem* pItem = AddNodeToItem(node);
    this->addTopLevelItem(pItem);

    this->expandAll();
}

QTreeWidgetItem* TreeWidget::AddNodeToItem(SceneNode* node)
{
    QTreeWidgetItem* pItem = new QTreeWidgetItem;
    pItem->setText(0, node->mName.c_str());

    QVariant data = QVariant::fromValue((void*)node);
    pItem->setData(0, Qt::UserRole, data);

    auto children = node->GetChildren();
    for(unsigned i = 0; i < children.size(); i++)
    {
        auto pChildItem = AddNodeToItem(children[i]);
        pItem->addChild(pChildItem);
    }

    return pItem;
}

void TreeWidget::itemClickSlot(QTreeWidgetItem* item)
{
    SceneNode* node = (SceneNode*) item->data(0, Qt::UserRole).value<void*>();

    char buf[512] = {0};
    const glm::vec3& pos = node->GetLocPosition();
    glm::vec3 angles = node->GetEulerAngles();
    glm::vec3 scale = node->GetLocScale();
    sprintf_s(buf, "name:%s\nposition : (%f, %f, %f)\nrotation : (%f, %f, %f)\nscale:(%f, %f, %f)", node->mName.c_str(),
             pos.x, pos.y, pos.z, angles.x, angles.y, angles.z, scale.x, scale.y, scale.z);


    QString str;
    str.append(buf);

    emit nodeProperty(str);

}
