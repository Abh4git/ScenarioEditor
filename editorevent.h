#ifndef EDITOREVENT_H
#define EDITOREVENT_H

#include <QEvent>

class EditorEvent : public QEvent {
public:
    static const QEvent::Type clearAll = static_cast<QEvent::Type>(2000);
    static const QEvent::Type openScene = static_cast<QEvent::Type>(2001);
    // ...
};


#endif // EDITOREVENT_H
