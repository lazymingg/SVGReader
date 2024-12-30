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
		cout << tokens[i] << '\n';

	for (auto &token : tokens)
	{
		if (token.find("translate") != string::npos)
		{
			stragetry.push_back(new Translate(token));
		}
		else if (token.find("scale") != string::npos)
		{
			stragetry.push_back(new Scale(token));
		}
		else if (token.find("rotate") != string::npos)
		{
			stragetry.push_back(new Rotate(token));
		}
	}
}

Transform::Transform(const Transform &transform)
{
	for (auto &a : transform.stragetry)
	{
		this->stragetry.push_back(a->clone());
	}
}

void Transform::transform(Gdiplus::Matrix &matrix)
{
	for (auto &stragetry : stragetry)
	{
		stragetry->transform(matrix);
	}
}
Transform &Transform::operator=(const Transform &transform)
{
	if (this == &transform)
	{
		return *this;
	}

	for (auto &stragetry : stragetry)
	{
		delete stragetry;
	}
	stragetry.clear();

	for (auto &stragetry : transform.stragetry)
	{
		this->stragetry.push_back(stragetry->clone());
	}

	return *this;
}

void Transform::addStragetry(Transform transform)
{
	for (auto &stragetry : transform.stragetry)
	{
		this->stragetry.push_back(stragetry->clone());
	}
}
Attribute *Transform::clone()
{
	return new Transform(*this);
}

Attribute *Transform::clone(string value)
{
	return new Transform(value);
}

Transform::~Transform()
{
	for (auto &stragetry : stragetry)
	{
		delete stragetry;
	}
	stragetry.clear();
}

void Transform::mergeData(Attribute *attribute)
{
    Transform *transform = dynamic_cast<Transform *>(attribute);
    if (transform)
    {
        addStragetry(*transform);
    }
}

string Transform::toString()
{
    string s = "Transforms:\n";
	int len = stragetry.size();

	if (len == 0)
		return s + "Empty";
	for (int i = 0; i < len; ++i)
	{
		s += stragetry[i]->toString();
		if (i != len - 1)
			s += "; ";
	}

	return s;
}
