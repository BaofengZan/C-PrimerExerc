#include <iostream>
#include <string>
#include <map>
#include <memory>

template<class ProductType_t, class ProdectImpl_t>
class ProdectRegistrar;


class RoleOperation
{
public:
	virtual std::string Op() = 0; // 纯虚函数，子类实现
	virtual ~RoleOperation() {} // 虚析构函数，防止释放指针时，没有释放掉子类指针，造成内存泄漏
};

// 针对不同的角色类，继承积累，并实现各自的功能
class RootAdminRole :public RoleOperation
{
public:
	RootAdminRole(const std::string& rolename) :m_RoleName(rolename)
	{
		//构造函数
	}

	std::string Op()
	{
		return m_RoleName + " has A permission";
	}
private:
	std::string m_RoleName;
};

// 订单管理
class OrderAdminRole :public RoleOperation
{
public:
	OrderAdminRole(const std::string rolename) : m_RoleName(rolename)
	{}
	std::string Op()
	{
		return m_RoleName + " has B permission";
	}
private:
	std::string m_RoleName;
};

// 普通用户
class NormalRole :public RoleOperation
{
public:
	NormalRole(const std::string rolename) :m_RoleName(rolename)
	{}

	std::string Op()
	{
		return m_RoleName + " has C permission";
	}
private:
	std::string m_RoleName;
};


//////////////////////////////////////////////////////////////////////////

//产品注册类模板接口
template <class ProductType_t>
class IProductRegistrar
{
public:
	virtual ProductType_t* CreateProduct(const std::string& name) = 0; //纯虚函数

protected:
	IProductRegistrar() {}
	virtual ~IProductRegistrar() {} // 虚析构
};


//  工厂模板类
template <class ProductType_t>  // ProduceType_t时基类，只要为产品基类（抽象产品类）
class ProductFactory
{
public:
	//获取工厂单类
	static ProductFactory<ProductType_t>& Instance()
	{
		static ProductFactory<ProductType_t> instance;
		return instance;
	}

	// 产品注册
	void RegisterProduct(const std::string& name, IProductRegistrar< ProductType_t>* registar)
	{
		m_ProductRegistry[name] = registar;
	}
	// 根据名字获取指针
	ProductType_t* GetProduct(const std::string& name)
	{
		if (m_ProductRegistry.find(name) != m_ProductRegistry.end())
		{
			return m_ProductRegistry[name]->CreateProduct(name);
		}

		std::cout << "No product found for" << name << std::endl;

		return NULL;
	}
	

private:
	ProductFactory() {}
	~ProductFactory() {}

	//禁止外部拷贝复制
	ProductFactory(const ProductFactory&);
	const ProductFactory& operator=(const ProductFactory&);

	//key val 保存注册过的角色
	std::map<std::string, IProductRegistrar< ProductType_t> *> m_ProductRegistry;
};

//ProdectImpl_t 为产品具体实现类
template<class ProductType_t, class ProdectImpl_t>
class ProductRegistrar : public IProductRegistrar<ProductType_t>
{
public:
	//构造函数 只能显示调用
	explicit ProductRegistrar(const std::string& name)
	{
		// 注册具体产品类到工厂
		ProductFactory<ProductType_t>::Instance().RegisterProduct(name, this);
	}

	//创建指向派生类对象的指针
	ProductType_t* CreateProduct(const std::string& name)
	{
		return new ProdectImpl_t(name);  // 每次都new
	}
};

void InitializeRole()
{
	static bool bInitialized = false;

	if (!bInitialized)
	{
		// 注册系统管理员
		static ProductRegistrar<RoleOperation, RootAdminRole> rootRegistrar("ROLE_ROOT_ADMIN");
		// 注册订单管理员
		static ProductRegistrar<RoleOperation, OrderAdminRole> orderRegistrar("ROLE_ORDER_ADMIN");
		// 注册普通用户
		static ProductRegistrar<RoleOperation, NormalRole> normalRegistrar("ROLE_NORMAL");
		bInitialized = true;
	}
}

class JudgeRole {
public:
	std::string Judge(const std::string &roleName) {
		ProductFactory<RoleOperation>& factory = ProductFactory<RoleOperation>::Instance();
		// 从工厂获取对应的指针对象
		RoleOperation *pRoleOperation = factory.GetProduct(roleName);
		// 调用角色的对应操作权限
		std::string result = pRoleOperation->Op();
		// 手动释放资源
		delete pRoleOperation;
		return result;
	}

	std::string Judge2(const std::string &roleName) {
		ProductFactory<RoleOperation>& factory = ProductFactory<RoleOperation>::Instance();
		std::shared_ptr<RoleOperation> pRoleOperation(factory.GetProduct(roleName)); //智能指针，防止内存泄漏
		return pRoleOperation->Op();
	}
};


int main()
{

	InitializeRole(); // 优先初始化所有角色到工厂

	JudgeRole judgeRole;

	std::cout << judgeRole.Judge("ROLE_ROOT_ADMIN") << std::endl;
	std::cout << judgeRole.Judge("ROLE_ORDER_ADMIN") << std::endl;
	std::cout << judgeRole.Judge("ROLE_NORMAL") << std::endl;

	std::cout << judgeRole.Judge2("ROLE_ROOT_ADMIN") << std::endl;
	std::cout << judgeRole.Judge2("ROLE_ORDER_ADMIN") << std::endl;
	std::cout << judgeRole.Judge2("ROLE_NORMAL") << std::endl;
	system("pause");
	return 0;
}