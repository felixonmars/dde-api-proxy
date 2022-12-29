#pragma once

#include "dbusproxybase.hpp"
#include "session_org_deepin_dde_daemon_Dock1_Entry.h"

class SessionDaemonDock1EntryProxy : public DBusProxyBase {
public:
    SessionDaemonDock1EntryProxy(QString dbusName, QString dbusPath, QString dbusInterface,
        QString proxyDbusName, QString proxyDbusPath, QString proxyDbusInterface,
        QDBusConnection::BusType dbusType, QObject *parent = nullptr) 
        : DBusProxyBase(dbusName, dbusPath, dbusInterface, proxyDbusName, proxyDbusPath, proxyDbusInterface, dbusType, parent)
    {
        // InitFilterProperies(QStringList({"DesktopFile", "IsActive", "Name", "Icon", "CurrentWindow", "IsDocked", "WindowInfos", "Id"}));
        // InitFilterMethods(QStringList({}));
        ServiceStart();
    }
    virtual DDBusExtendedAbstractInterface *initConnect()
    {
        m_dbusProxy = new org::deepin::dde::daemon::dock1::Entry(m_dbusName, m_dbusPath, QDBusConnection::sessionBus(), this);
        return m_dbusProxy;
    }
private:
    org::deepin::dde::daemon::dock1::Entry *m_dbusProxy;
};


