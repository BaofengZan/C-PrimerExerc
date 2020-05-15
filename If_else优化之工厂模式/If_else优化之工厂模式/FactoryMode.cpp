//#include <iostream>
//#include <string>
//#include <map>
//
//class RoleOperation
//{
//public:
//	virtual std::string Op() = 0; // ���麯��������ʵ��
//	virtual ~RoleOperation() {} // ��������������ֹ�ͷ�ָ��ʱ��û���ͷŵ�����ָ�룬����ڴ�й©
//};
//
//// ��Բ�ͬ�Ľ�ɫ�࣬�̳л��ۣ���ʵ�ָ��ԵĹ���
//class RootAdminRole :public RoleOperation
//{
//public:
//	RootAdminRole(const std::string& rolename):m_RoleName(rolename)
//	{
//		//���캯��
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
//// ��������
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
//// ��ͨ�û�
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
//// ������
////���������ӿ�
////1 ע�����Ʒ���ָ��
////2 ��ȡ��ָ��
//
//class RoleFactory
//{
//public:
//	/*
//	��ʱ��Ϊ���캯����class˽�л�����������Ҫ���������󣬾ͱ����ܹ����ʵ�class��˽����
//	��һ��ֻ��class�ĳ�Ա�������õ����������ǽ����������֮ǰ����ô���������ĳ�Ա�أ�
//	static���г�Ա�����Ƕ�����class��������ڵģ������ǡ����Է��ʵõ���
//	������ĳ��static�����д����˸�class�Ķ��󣬲������û���ָ�����ʽ���䷵�أ����ﲻ
//	�Զ��󷵻أ���Ҫ�ǹ��캯����˽�еģ��ⲿ���ܴ�����ʱ���󣩣��ͻ������������ʹ��Ȩ��
//	*/
//
//	// �������ã������൱�ڷ��ض���
//	static RoleFactory& Instance()
//	{
//		static RoleFactory instance;
//		return instance; // static ���ⲿ���Է��ʵĵ�
//	}
//
//	// ע�ᣬ������map����ֵ
//	void RegisterRole(const std::string& name, RoleOperation* registrar)
//	{
//		m_RoleRegistry[name] = registrar;
//	}
//
//	// ����name ��ȡ��Ӧ��ɫ��ָ��
//	RoleOperation* GetRole(const std::string& name)
//	{
//		std::map<std::string, RoleOperation*>::iterator it;
//		//��map���ҵ��Ѿ�ע����Ľ�ɫ��������ָ��
//		it = m_RoleRegistry.find(name);
//		if (it!= m_RoleRegistry.end())
//		{
//			return it->second;
//		}
//		return nullptr;
//	}
//private:
//	// ˽�й����������ʵ�ֵ���ģʽ
//	//���캯��˽�л��������Ʊ�֤�������಻�ܴ�������������ߴ������ʵ��
//	//������α�ֻ֤���ڶ���newһ���µ�������أ�ֻ���������������Ϊ˽�г�Ա��
//	RoleFactory() {}
//	~RoleFactory() {}
//
//	//��ֹ�ⲿ��������
//	RoleFactory(const RoleFactory&);
//	const RoleFactory& operator=(const RoleFactory&);
//
//	//key val ����ע����Ľ�ɫ
//	std::map<std::string, RoleOperation*> m_RoleRegistry;
//}; 
//
//
////////////////////////////////////////////////////////////////////////////
////��ʼ�����н�ɫ������������װ����ʼ������
////�����Ҫ����µĽ�ɫ��ֻ��Ҫʵ�ָ��ԵĹ����࣬���ڸú�����ע�ἴ��
//void InitializeRole()
//{
//	static bool bInitialized = false; // ȫ�ֿ���
//	if (bInitialized == false)
//	{
//		// ע��ϵͳ����Ա
//		RoleFactory::Instance().RegisterRole("ROLE_ROOT_ADMIN", new RootAdminRole("ROLE_ROOT_ADMIN"));
//		// ע�ᶩ������Ա
//		RoleFactory::Instance().RegisterRole("ROLE_ORDER_ADMIN", new OrderAdminRole("ROLE_ORDER_ADMIN"));
//		// ע����ͨ�û�
//		RoleFactory::Instance().RegisterRole("ROLE_NORMAL", new NormalRole("ROLE_NORMAL"));
//
//		bInitialized = true;
//	}
//}
//
////�ͻ�����
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
//	InitializeRole(); // ���ȳ�ʼ�����н�ɫ������
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