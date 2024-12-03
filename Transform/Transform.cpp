#include "Transform.h"

Transform::Transform()
{
    stragetry.push_back(new Translate("translate(0,0)"));
}

Transform::Transform(string str)
{
    vector<string> tokens;
    int len = str.length();

    string get = "";

    for (int i = 0; i <= len; i++)
    {
        if ((str[i] == ' ' && str[i - 1] == ')') || i == len)
        {
            tokens.push_back(get);
            get = "";
        }
        else
            get += str[i];
    }

    for (int i = 0; i < tokens.size(); i++)
        this->setTransform(tokens[i]);

    len = tokens.size();
    for (int i = 0; i < len; i++)
        tokens.pop_back();
}

MyMatrix::Matrix Transform::doTransform(MyMatrix::Matrix matrix)
{
    cout << stragetry.size();

   for (int i = 0; i < stragetry.size(); i++)
       matrix = stragetry[i]->doTransform(matrix);
    return matrix;
}

void Transform::setTransform(string str)
{
    size_t openBracket = str.find("(");
    size_t closeBracket = str.find(")");
    string transform = str.substr(0, openBracket);

    if (transform == "translate")
    {
        cout << "Translate" << endl;
        stragetry.push_back(new Translate(str));
    }
    else if (transform == "scale")
    {
        stragetry.push_back(new Scale(str));
    }
    else if (transform == "rotate")
    {
        stragetry.push_back(new Rotate(str));
    }
}

Transform::~Transform()
{
    int len = stragetry.size();
    for (int i = len - 1; i >= 0; i--)
    {
        delete stragetry[i];
        stragetry.pop_back();
    }
}
