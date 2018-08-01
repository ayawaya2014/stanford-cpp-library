/*
 * File: qgobservable.h
 * ---------------------
 *
 * @version 2018/07/11
 * - initial version
 */

#ifdef SPL_QT_GUI
#ifndef _qgobservable_h
#define _qgobservable_h

#include <functional>
#include <string>
#include <QObject>
#include <QWidget>
#include <QWindow>
#include <QEvent>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QTimerEvent>
#include <QWheelEvent>
#include <QWindowStateChangeEvent>
#include "map.h"
#include "qgevent.h"

/*
 * ...
 */
class QGObservable {
public:
    QGObservable();
    virtual ~QGObservable();

    virtual bool eventsEnabled() const;
    virtual std::string getType() const = 0;
    virtual void setEventsEnabled(bool eventsEnabled);
    virtual std::string toString() const;

protected:
    virtual void clearEventListeners();
    virtual void ensureThreadSafety(const std::string& memberName = "");
    virtual void fireEvent(QGEvent& event);
    virtual void fireQGEvent(QEvent* event, QGEvent::EventType eventType, const std::string& eventName);
    virtual void fireQGEvent(QCloseEvent* event, QGEvent::EventType eventType, const std::string& eventName);
    virtual void fireQGEvent(QKeyEvent* event, QGEvent::EventType eventType, const std::string& eventName);
    virtual void fireQGEvent(QMouseEvent* event, QGEvent::EventType eventType, const std::string& eventName, const std::string& actionCommand = "");
    virtual void fireQGEvent(QResizeEvent* event, QGEvent::EventType eventType, const std::string& eventName);
    virtual void fireQGEvent(QTimerEvent* event, QGEvent::EventType eventType, const std::string& eventName);
    virtual void fireQGEvent(QWheelEvent* event, QGEvent::EventType eventType, const std::string& eventName);
    virtual void fireQGEvent(QWindowStateChangeEvent* event, QGEvent::EventType eventType, const std::string& eventName);
    virtual bool hasEventListener(const std::string& eventName) const;
    virtual void removeEventListener(const std::string& eventName);
    virtual void removeEventListeners(std::initializer_list<std::string> eventNames);
    virtual void setEventListener(const std::string& eventName, QGEventListener func);
    virtual void setEventListener(const std::string& eventName, QGEventListenerVoid func);
    virtual void setEventListeners(std::initializer_list<std::string> eventNames, QGEventListener func);
    virtual void setEventListeners(std::initializer_list<std::string> eventNames, QGEventListenerVoid func);

    Map<std::string, QGEvent::EventListenerWrapper> _eventMap;
    bool _eventsEnabled;
};

#include "private/init.h"   // ensure that Stanford C++ lib is initialized

#endif // _qgobservable_h
#endif // SPL_QT_GUI