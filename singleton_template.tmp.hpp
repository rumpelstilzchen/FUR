class Singleton
{
private: 
  //singleton foo
  Singleton() {}
  ~Singleton() {} 
  Singleton(const Singleton &);             // intentionally undefined
  Singleton & operator=(const Singleton &); // intentionally undefined

public:
  //singleton foo
  static Singleton &getInstance();
};
