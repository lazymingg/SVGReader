#include "Transform.h"

Transform::Transform()
{
    stragetry = new Translate("translate(0,0)");
}

Transform::Transform(string str)
{
    size_t openBracket = str.find("(");
    size_t closeBracket = str.find(")");
    string transform = str.substr(0, openBracket);

    if (transform == "translate")
    {
        cout << "Translate" << endl;
        stragetry = new Translate(str);
    }
    else if (transform == "scale")
    {
        stragetry = new Scale(str);
    }
    else if (transform == "rotate")
    {
        stragetry = new Rotate(str);
    }
    else
    {
        // no transform here default translate with 0,0
        stragetry = new Translate("translate(0,0)");
    }
}

void Transform::transform(MyMatrix::Matrix &matrix)
{
    stragetry->transform(matrix);
}
