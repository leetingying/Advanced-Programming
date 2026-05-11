#ifndef MYTEMPLATE_H
#define MYTEMPLATE_H	

template <typename T>
double scalar_difference(T pt1, T pt2)
{
	double t1, t2;
	t1 = pt1.getScalarValue();
	t2 = pt2.getScalarValue();
	
	if (t1 > t2)
	{
		return t1 - t2;
	}
	else
	{
		return t2 - t1;
	}
}

template <typename T>
bool equals(T pt1, T pt2)
{
	if (pt1 == pt2)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

template <typename T>
void removeDuplicate(std::vector<T>& v)
{
	for (int i = 0; i < v.size() - 1; i++)
	{
		while (i + 1 <= v.size() - 1 && equals(v[i],v[i+1]))
		{
			v.erase(v.begin() + i + 1);
		}
	}
}


#endif
