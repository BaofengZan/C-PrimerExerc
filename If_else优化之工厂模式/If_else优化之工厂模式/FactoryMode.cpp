//#include <iostream>
//#include <string>
//#include <map>
//
//class RoleOperation
//{
//public:
//	virtual std::string Op() = 0; // 纯虚函数，子类实现
//	virtual ~RoleOperation() {} // 虚析构函数，防止释放指针时，没有释放掉子类指针，造成内存泄漏
//};
//
//// 针对不同的角色类，继承积累，并实现各自的功能
//class RootAdminRole :public RoleOperation
//{
//public:
//	RootAdminRole(const std::string& rolename):m_RoleName(rolename)
//	{
//		//构造函数
//	}
//
//	std::string Op()
//	{
//		return m_RoleName + " has A permission";
//	}
//private: 
//	std::string m_RoleName;
//};
//
//// 订单管理
//class OrderAdminRole :public RoleOperation
//{
//public:
//	OrderAdminRole(const std::string rolename): m_RoleName(rolename)
//	{}
//	std::string Op()
//	{
//		return m_RoleName + " has B permission";
//	}
//private:
//	std::string m_RoleName;
//};
//
//// 普通用户
//class NormalRole:public RoleOperation
//{
//public:
//	NormalRole(const std::string rolename) :m_RoleName(rolename)
//	{}
//
//	std::string Op()
//	{
//		return m_RoleName + " has C permission";
//	}
//private:
//	std::string m_RoleName;
//};
//
//
//// 工厂类
////包含两个接口
////1 注册各产品类的指针
////2 获取各指针
//
//class RoleFactory
//{
//public:
//	/*
//	此时因为构造函数被class私有化，所以我们要创建出对象，就必须能够访问到class的私有域；
//	这一点只有class的成员可以做得到；但在我们建构出其对象之前，怎么能利用它的成员呢？
//	static公有成员，它是独立于class对象而存在的，“我们”可以访问得到。
//	假如在某个static函数中创建了该class的对象，并以引用或者指针的形式将其返回（这里不
//	以对象返回，主要是构造函数是私有的，外部不能创建临时对象），就获得了这个对象的使用权。
//	*/
//
//	// 返回引用，就是相当于返回对象
//	static RoleFactory& Instance()
//	{
//		static RoleFactory instance;
//		return instance; // static 类外部可以访问的到
//	}
//
//	// 注册，就是往map中塞值
//	void RegisterRole(const std::string& name, RoleOperation* registrar)
//	{
//		m_RoleRegistry[name] = registrar;
//	}
//
//	// 根据name 获取对应角色的指针
//	RoleOperation* GetRole(const std::string& name)
//	{
//		std::map<std::string, RoleOperation*>::iterator it;
//		//从map中找到已经注册过的角色，并返回指针
//		it = m_RoleRegistry.find(name);
//		if (it!= m_RoleRegistry.end())
//		{
//			return it->second;
//		}
//		return nullptr;
//	}
//private:
//	// 私有构造和析构：实现单例模式
//	//构造函数私有化的类的设计保证了其他类不能从这个类派生或者创建类的实例
//	//另外如何保证只能在堆上new一个新的类对象呢？只需把析构函数定义为私有成员。
//	RoleFactory() {}
//	~RoleFactory() {}
//
//	//禁止外部拷贝复制
//	RoleFactory(const RoleFactory&);
//	const RoleFactory& operator=(const RoleFactory&);
//
//	//key val 保存注册过的角色
//	std::map<std::string, RoleOperation*> m_RoleRegistry;
//}; 
//
//
////////////////////////////////////////////////////////////////////////////
////初始化所有角色到工厂，并封装到初始化函数
////如果需要添加新的角色，只需要实现各自的功能类，并在该函数中注册即可
//void InitializeRole()
//{
//	static bool bInitialized = false; // 全局可用
//	if (bInitialized == false)
//	{
//		// 注册系统管理员
//		RoleFactory::Instance().RegisterRole("ROLE_ROOT_ADMIN", new RootAdminRole("ROLE_ROOT_ADMIN"));
//		// 注册订单管理员
//		RoleFactory::Instance().RegisterRole("ROLE_ORDER_ADMIN", new OrderAdminRole("ROLE_ORDER_ADMIN"));
//		// 注册普通用户
//		RoleFactory::Instance().RegisterRole("ROLE_NORMAL", new NormalRole("ROLE_NORMAL"));
//
//		bInitialized = true;
//	}
//}
//
////客户代码
//class JudgeRole
//{
//public: 
//	std::string Judge(const std::string& rolename)
//	{
//		return RoleFactory::Instance().GetRole(rolename)->Op(); 
//	}
//};
//
//int main0()
//{
//
//	InitializeRole(); // 优先初始化所有角色到工厂
//
//	JudgeRole judgeRole;
//
//	std::cout << judgeRole.Judge("ROLE_ROOT_ADMIN") << std::endl;
//	std::cout << judgeRole.Judge("ROLE_ORDER_ADMIN") << std::endl;
//	std::cout << judgeRole.Judge("ROLE_NORMAL") << std::endl;
//
//	system("pause");
//	return 0;
//}