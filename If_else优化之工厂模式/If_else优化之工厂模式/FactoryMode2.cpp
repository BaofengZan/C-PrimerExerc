#include <iostream>
#include <string>
#include <map>
#include <memory>

template<class ProductType_t, class ProdectImpl_t>
class ProdectRegistrar;


class RoleOperation
{
public:
	virtual std::string Op() = 0; // ���麯��������ʵ��
	virtual ~RoleOperation() {} // ��������������ֹ�ͷ�ָ��ʱ��û���ͷŵ�����ָ�룬����ڴ�й©
};

// ��Բ�ͬ�Ľ�ɫ�࣬�̳л��ۣ���ʵ�ָ��ԵĹ���
class RootAdminRole :public RoleOperation
{
public:
	RootAdminRole(const std::string& rolename) :m_RoleName(rolename)
	{
		//���캯��
	}

	std::string Op()
	{
		return m_RoleName + " has A permission";
	}
private:
	std::string m_RoleName;
};

// ��������
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

// ��ͨ�û�
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

//��Ʒע����ģ��ӿ�
template <class ProductType_t>
class IProductRegistrar
{
public:
	virtual ProductType_t* CreateProduct(const std::string& name) = 0; //���麯��

protected:
	IProductRegistrar() {}
	virtual ~IProductRegistrar() {} // ������
};


//  ����ģ����
template <class ProductType_t>  // ProduceType_tʱ���ֻ࣬ҪΪ��Ʒ���ࣨ�����Ʒ�ࣩ
class ProductFactory
{
public:
	//��ȡ��������
	static ProductFactory<ProductType_t>& Instance()
	{
		static ProductFactory<ProductType_t> instance;
		return instance;
	}

	// ��Ʒע��
	void RegisterProduct(const std::string& name, IProductRegistrar< ProductType_t>* registar)
	{
		m_ProductRegistry[name] = registar;
	}
	// �������ֻ�ȡָ��
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

	//��ֹ�ⲿ��������
	ProductFactory(const ProductFactory&);
	const ProductFactory& operator=(const ProductFactory&);

	//key val ����ע����Ľ�ɫ
	std::map<std::string, IProductRegistrar< ProductType_t> *> m_ProductRegistry;
};

//ProdectImpl_t Ϊ��Ʒ����ʵ����
template<class ProductType_t, class ProdectImpl_t>
class ProductRegistrar : public IProductRegistrar<ProductType_t>
{
public:
	//���캯�� ֻ����ʾ����
	explicit ProductRegistrar(const std::string& name)
	{
		// ע������Ʒ�ൽ����
		ProductFactory<ProductType_t>::Instance().RegisterProduct(name, this);
	}

	//����ָ������������ָ��
	ProductType_t* CreateProduct(const std::string& name)
	{
		return new ProdectImpl_t(name);  // ÿ�ζ�new
	}
};

void InitializeRole()
{
	static bool bInitialized = false;

	if (!bInitialized)
	{
		// ע��ϵͳ����Ա
		static ProductRegistrar<RoleOperation, RootAdminRole> rootRegistrar("ROLE_ROOT_ADMIN");
		// ע�ᶩ������Ա
		static ProductRegistrar<RoleOperation, OrderAdminRole> orderRegistrar("ROLE_ORDER_ADMIN");
		// ע����ͨ�û�
		static ProductRegistrar<RoleOperation, NormalRole> normalRegistrar("ROLE_NORMAL");
		bInitialized = true;
	}
}

class JudgeRole {
public:
	std::string Judge(const std::string &roleName) {
		ProductFactory<RoleOperation>& factory = ProductFactory<RoleOperation>::Instance();
		// �ӹ�����ȡ��Ӧ��ָ�����
		RoleOperation *pRoleOperation = factory.GetProduct(roleName);
		// ���ý�ɫ�Ķ�Ӧ����Ȩ��
		std::string result = pRoleOperation->Op();
		// �ֶ��ͷ���Դ
		delete pRoleOperation;
		return result;
	}

	std::string Judge2(const std::string &roleName) {
		ProductFactory<RoleOperation>& factory = ProductFactory<RoleOperation>::Instance();
		std::shared_ptr<RoleOperation> pRoleOperation(factory.GetProduct(roleName)); //����ָ�룬��ֹ�ڴ�й©
		return pRoleOperation->Op();
	}
};


int main()
{

	InitializeRole(); // ���ȳ�ʼ�����н�ɫ������

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