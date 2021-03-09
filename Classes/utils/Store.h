#include <mutex>
#include <map>
#include <string>

class Store
{

private:
    static Store* pinstance_;
    static std::mutex mutex_;

protected:
    Store();
    ~Store();

public:
    Store(Store& other) = delete;
    void operator=(const Store&) = delete;
    static Store* GetInstance();

    // ###################################################
    // Declarations
    // ###################################################

    std::string g_mapName;
    
};
