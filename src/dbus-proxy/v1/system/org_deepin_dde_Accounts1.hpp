#pragma once

#include "dbusproxybase.hpp"
#include "system_org_deepin_dde_Accounts1.h"

#include "system/org_deepin_dde_Accounts1_User.hpp"

class SystemAccounts1Proxy : public DBusProxyBase {
public:
    SystemAccounts1Proxy(QString dbusName, QString dbusPath, QString dbusInterface,
        QString proxyDbusName, QString proxyDbusPath, QString proxyDbusInterface,
        QDBusConnection::BusType dbusType, QObject *parent = nullptr) 
        : DBusProxyBase(dbusName, dbusPath, dbusInterface, proxyDbusName, proxyDbusPath, proxyDbusInterface, dbusType, parent)
    {
        InitFilterProperies(QStringList({"UserList"}));
        InitFilterMethods(QStringList({"EnablePasswdChangedHandler", "FindUserByName"}));
        ServiceStart();
    }
    virtual DBusExtendedAbstractInterface *initConnect()
    {
        m_dbusProxy = new org::deepin::dde::Accounts1(m_dbusName, m_dbusPath, QDBusConnection::systemBus(), this);
        return m_dbusProxy;
    }
    virtual void signalMonitorCustom()
    {
        QString subPathInterface  = "org.deepin.dde.Accounts1.User";
        QString subPathProxyInterface;
        QString subPathProxyPathPrefix;
        if (m_proxyDbusName == "com.deepin.daemon.Accounts") {
            // V0 -> V1子PATH处理
            subPathProxyInterface = "com.deepin.daemon.Accounts.User";
            subPathProxyPathPrefix = "/com/deepin/daemon/Accounts/";
        } else if (m_proxyDbusName == "org.deepin.daemon.Accounts1") {
            // V0.5 -> V1子PATH处理
            subPathProxyInterface = "org.deepin.daemon.Accounts1.User";
            subPathProxyPathPrefix = "/org/deepin/daemon/Accounts1/";
        }
        SubPathInit("UserList", [=](QString path){
            QString suffix = path.right(path.size() - (path.lastIndexOf("/") + 1));
            QString proxyPath = subPathProxyPathPrefix + suffix;
            qInfo() << "create accounts.User path proxy:" << proxyPath << "to" << path;
            return new SystemAccounts1UserProxy(m_dbusName, 
                path, 
                subPathInterface, 
                m_proxyDbusName, 
                proxyPath, 
                subPathProxyInterface,
                m_dbusType);
            });
    }
private:
    org::deepin::dde::Accounts1 *m_dbusProxy;
};


