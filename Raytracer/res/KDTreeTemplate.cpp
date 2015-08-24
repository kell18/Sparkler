

class X
{
};

class BB
{
public:
  bool isNullBB;
  bool isIntWith(const Ray& ray) {
    return isNullBB;
  }
  BB(bool isNullBB) : isNullBB(isNullBB) {}
};

BB notNullBB = BB(true);
BB nullBB = BB(true);

class KDElement
{
public:
  KDElement* major;
  KDElement* minor;
  vector<X*> Xs;
  BB bb;


  KDElement(KDElement* major, KDElement* minor, vector<X*> Xs, BB bb)
    : major(major), minor(minor), Xs(Xs), bb(bb)
  {
  }
};

KDElement *nullKDElement = new KDElement(nullptr, nullptr, vector<X*>(), nullBB);

class KDNode : public KDElement
{
public:
  KDNode(KDElement* major, KDElement* minor, BB bb)
    : KDElement(major, minor, vector<X*>(), bb)
  {
  }
};

class KDLeaf : private KDElement
{
public:
  KDLeaf(vector<X*> Xs, BB bb)
    : KDElement(nullKDElement, nullKDElement, Xs, bb)
  {
  }
};

vector<X*> findNearestDisplayObjects(KDElement *startElement, const Ray& ray)
{
  if(startElement->major->bb.isIntWith(ray)) {
    return findNearestDisplayObjects(startElement->major, ray);
  } else if (startElement->minor->bb.isIntWith(ray)) {
    return findNearestDisplayObjects(startElement->minor, ray);
  }
  return startElement->Xs;
}