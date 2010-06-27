Singleton& Singleton::getInstance()
{
  static Singleton instance;
  return instance;
}
