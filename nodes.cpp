#include "nodes.h"
#include <QDebug>
#include <vector>
#include <fstream>

Nodes::Nodes(QObject*parent):QObject{parent} {}

void Nodes::setInlet(QString newInlet)
{
    inlet=newInlet;
}

void Nodes::setOutlet(QString newOutlet)
{
    outlet=newOutlet;
}

QString Nodes::getInlet() const
{
    return inlet;
}

QString Nodes::getOutlet() const
{
    return outlet;
}

QString Nodes::getFullText() const
{
    return fullText;
}

void Nodes::serialize()
{
    std::string inlet_string=inlet.toStdString();
    std::fstream in(inlet_string);
    std::string line;
    std::string word;
    int number;
    std::vector<std::pair<std::string, int>> inletData;//промежуточное хранение
    while (std::getline(in, line)) {
        // найти позицию символа ';'
        std::size_t pos = line.find(';');
        // если разделитель найден
        if (pos != std::string::npos) {
            // слово до ';'
            word = line.substr(0, pos);
            // строка после ';'
            std::string numString = line.substr(pos + 1);
            // преобразовать строку в число
            number = std::stoi(numString);
        }
        inletData.push_back(std::make_pair(word, number));
    }
    in.close();
    ListNode* head=new ListNode;//голова списка
    std::vector<ListNode*> nodes(inletData.size());//узлы
    for (int j = 0; j < inletData.size(); j++) {
        nodes[j] = new ListNode;
        nodes[j]->data = inletData[j].first;
    }
    for (int j = 0; j < inletData.size(); j++) {
        if (inletData[j].second >= 0) { nodes[j]->rand = nodes[inletData[j].second]; }
        if (j < inletData.size() - 1) { nodes[j]->next = nodes[j + 1]; }
        if (j == 0) {
            head = nodes[j];
        }
        else nodes[j]->prev = nodes[j - 1];
    }
    std::string outlet_string=outlet.toStdString();
    std::ofstream out(outlet_string, std::ios::binary);
    // узлы в вектор
    std::vector<ListNode*> order;
    for (ListNode* cur = head; cur; cur = cur->next)
        order.push_back(cur);

    // количество узлов
    int count = (int)order.size();
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));

    // 3) data и индексы rand
    for (int i = 0; i < count; i++) {
        // data
        const std::string& s = order[i]->data;
        int len = (int)s.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(s.data(), len);

        // rand
        int randIndex = -1;
        if (order[i]->rand) {
            //  позиция узла, на который указывает rand
            randIndex = (int)(std::find(order.begin(), order.end(), order[i]->rand) - order.begin());
        }
        out.write(reinterpret_cast<const char*>(&randIndex), sizeof(randIndex));
    }
}

void Nodes::deserialize()
{
    std::string outlet_string=outlet.toStdString();
    std::ifstream in(outlet_string, std::ios::binary);
    if (!in.is_open()) return;

    // количество узлов
    int count;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));

    // //промежуточное хранение
    struct Tmp { std::string data; int randIndex; };
    std::vector<Tmp> tmp(count);

    for (int i = 0; i < count; i++)
    {
        //  длина строки
        int len;
        in.read(reinterpret_cast<char*>(&len), sizeof(len));

        // строка
        std::string str(len, '\0');
        in.read(&str[0], len);

        // rand индекс
        int randIndex;
        in.read(reinterpret_cast<char*>(&randIndex), sizeof(randIndex));

        tmp[i] = { str, randIndex };
    }
    in.close();

    fullText=nullptr;
    // запись строки вида "data;randIndex"
    for (int i = 0; i < count; i++)
    {
        fullText += QString::fromStdString(tmp[i].data) + ";" +
                    QString::number(tmp[i].randIndex) + "\n";
    }

    emit fullTextSignal(fullText);
}






