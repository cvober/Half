#include<iostream>

public class Node 
{
    private: 
        int frequence;//частота
        char letter;//буква
        Node leftChild;//левый потомок
        Node rightChild;//правый потомок

    public:
        Node(char letter, int frequence) 
        { //собственно, конструктор
            this.letter = letter;
            this.frequence = frequence;
        };
        Node() {}//перегрузка конструтора для безымянных узлов(см. выше в разделе о построении дерева Хаффмана)
        
    public:
        void addChild(Node newNode) 
        {//добавить потомка
            if (leftChild == null)//если левый пустой=> правый тоже=> добавляем в левый
                leftChild = newNode;

            else {
                if (leftChild.getFrequence() <= newNode.getFrequence()) //в общем, левым потомком
                    rightChild = newNode;//станет тот, у кого меньше частота

                else 
                {
                    rightChild = leftChild;
                    leftChild = newNode;
                }
            }
            frequence += newNode.getFrequence();//итоговая частота
        }

    Node getLeftChild() 
    {
        return leftChild;
    }

    Node getRightChild() 
    {
        return rightChild;
    }

    int getFrequence() 
    {
        return frequence;
    }

    char getLetter() 
    {
        return letter;
    }

    boolean isLeaf() 
    {//проверка на лист
        return leftChild == null && rightChild == null;
    }
};







