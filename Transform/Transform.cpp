#include "Transform.h"

Transform::Transform(string str)
{
    size_t openBracket = str.find("(");
    size_t closeBracket = str.find(")");
    string transform = str.substr(0, openBracket);

    if (transform == "translate")
    {
        size_t comma = str.find(",");
        int dx = stoi(str.substr(openBracket + 1, comma - openBracket - 1));
        int dy = stoi(str.substr(comma + 1, closeBracket - comma - 1));
        stragetry = new Translate(dx, dy);
    }
    else if (transform == "scale")
    {
        size_t comma = str.find(",");
        int sx = stoi(str.substr(openBracket + 1, comma - openBracket - 1));
        int sy = stoi(str.substr(comma + 1, closeBracket - comma - 1));
        stragetry = new Scale(sx, sy);
    }
    else if (transform == "rotate")
    {
        int angle = stoi(str.substr(openBracket + 1, closeBracket - openBracket - 1));
        stragetry = new Rotate(angle);
    }
    else
    {
        cout << "Invalid transform" << endl;
    }
}

void Transform::transform(MyMatrix::Matrix &matrix)
{
    stragetry->transform(matrix);
}
