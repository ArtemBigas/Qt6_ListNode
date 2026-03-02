#ifndef NODES_H
#define NODES_H

#include <QObject>

class Nodes:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString inlet_qml READ getInlet WRITE setInlet NOTIFY inletSignal)
    Q_PROPERTY(QString outlet_qml READ getOutlet WRITE setOutlet NOTIFY outletSignal)
    Q_PROPERTY(QString fullText_qml READ getFullText  NOTIFY fullTextSignal)
public:
    explicit Nodes(QObject*parent=nullptr);
    Q_INVOKABLE void serialize();
    Q_INVOKABLE void deserialize();
    QString getInlet()const;
    QString getOutlet()const;
    QString getFullText()const;
    void setInlet(QString newInlet);
    void setOutlet(QString newOutlet);
signals:
    void inletSignal( QString);
    void outletSignal( QString);
    void fullTextSignal( QString);
private:
    struct ListNode { // ListNode модифицировать нельзя
        ListNode* prev = nullptr; // указатель на предыдущий элемент или nullptr
        ListNode* next = nullptr;
        ListNode* rand = nullptr; // указатель на произвольный элемент данного списка, либо `nullptr`
        std::string data; // произвольные пользовательские данные
    };
    QString inlet="inlet.in";
    QString outlet="outlet.out";
    QString fullText{};

};

#endif // NODES_H
