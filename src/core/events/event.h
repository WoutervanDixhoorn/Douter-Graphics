#pragma once

#include <format>
#include <string>

#include "keys.h"
#include "buttons.h"

namespace DG {

    enum class EventType {
        KeyPressedEvent,
        KeyReleasedEvent,

        MouseMovedEvent,
        MouseScrolledEvent,
        MousePressedEvent,
        MouseReleasedEvent,

        WindowResizeEvent,
        WindowCloseEvent,
        WindowMinimizeEvent,
        WindowRestoreEvent,
        WindowMaximizeEvent
    };

#define DG_EVENT_TYPE(type) \
    static EventType GetStaticType() { return EventType::type; } \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char* GetName() const override { return #type; }

    class IEvent {
    public:
        IEvent() = default;
        virtual ~IEvent() = default;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual std::string ToString() const { return GetName(); };

        bool Handled = false;
    };

    class EventDispatcher {
    public:
        EventDispatcher(IEvent& event) : m_event(event) {};
        virtual ~EventDispatcher() = default;

        template <typename T, typename F>
        bool Dispatch(const F& func) {
            if (m_event.GetEventType() == T::GetStaticType()) {
                m_event.Handled |= func(static_cast<T&>(m_event));
                return true;
            }
            return false;
        }

    private:
        IEvent& m_event;

    };

    class KeyPressedEvent : public IEvent {
    private:
        KeyCode m_key;

    public:
        KeyPressedEvent(const KeyCode key) : m_key(key) {}

        DG_EVENT_TYPE(KeyPressedEvent);

        KeyCode GetKey() const { return m_key; }
        std::string ToString() const override { return std::format("[KeyPressedEvent] Key: {}", m_key); }
    };

    class KeyReleasedEvent : public IEvent {
    private:
        KeyCode m_key;

    public:
        KeyReleasedEvent(const KeyCode key) : m_key(key) {}

        DG_EVENT_TYPE(KeyPressedEvent);

        KeyCode GetKey() const { return m_key; }
        std::string ToString() const override { return std::format("[KeyReleasedEvent] Key: {}", m_key); }
    };

    class MouseMovedEvent : public IEvent {
    private:
        double m_x, m_y;

    public:
        MouseMovedEvent(const double x, const double y) : m_x(x), m_y(y) {}

        DG_EVENT_TYPE(MouseMovedEvent);

        double GetX() const { return m_x; }
        double GetY() const { return m_x; }
        std::string ToString() const override { return std::format("[MouseMovedEvent] X: {:.2f}, Y: {:.2f}", m_x, m_y); }
    };

    class MouseScrolledEvent : public IEvent {
    private:
        double m_xOffset, m_yOffset;

    public:
        MouseScrolledEvent(const double xOffset, const double yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}

        DG_EVENT_TYPE(MouseScrolledEvent);

        double GetXOffset() const { return m_xOffset; }
        double GetYOffset() const { return m_yOffset; }
        std::string ToString() const override { return std::format("[MouseScrolledEvent] X: {:.2f}, Y: {:.2f}", m_xOffset, m_yOffset); };
    };

    class MousePressedEvent : public IEvent {
    private:
        ButtonCode m_button;

    public:
        MousePressedEvent(const ButtonCode button) : m_button(button) {}

        DG_EVENT_TYPE(MousePressedEvent);

        ButtonCode GetButton() const { return m_button; }
        std::string ToString() const override { return std::format("[MousePressedEvent] Button: {}", m_button); };
    };

    class MouseReleasedEvent : public IEvent {
    private:
        ButtonCode m_button;

    public:
        MouseReleasedEvent(const ButtonCode button) : m_button(button) {}

        DG_EVENT_TYPE(MouseReleasedEvent);

        ButtonCode GetButton() const { return m_button; }
        std::string ToString() const override { return std::format("[MouseReleasedEvent] Button: {}", m_button); };
    };

    class WindowResizeEvent : public IEvent {
    private:
        int m_width, m_height;

    public:
        WindowResizeEvent(const int width, const int height) : m_width(width), m_height(height) {}

        DG_EVENT_TYPE(WindowResizeEvent);

        int GetWidth() const { return m_width; }
        int GetHeight() const { return m_height; }
        std::string ToString() const override { return std::format("[WindowResizeEvent] X: {}, Y: {}", m_width, m_height); };
    };

    class WindowCloseEvent : public IEvent {
    public:
        WindowCloseEvent() {};

        DG_EVENT_TYPE(WindowCloseEvent);
    };

    class WindowMinimizeEvent : public IEvent {
    private:
        bool m_isMinimized;

    public:
        WindowMinimizeEvent(bool isMinimized) : m_isMinimized(isMinimized) {};

        DG_EVENT_TYPE(WindowMinimizeEvent);

        bool IsMinimized() const { return m_isMinimized; }
        std::string ToString() const override { return std::format("[WindowMinimizeEvent] Is minimized: {}", m_isMinimized); };
    };

    class WindowMaximizeEvent : public IEvent {
    private:
        bool m_isMaximized;

    public:
        WindowMaximizeEvent(bool isMaximized) : m_isMaximized(isMaximized) {};

        DG_EVENT_TYPE(WindowMaximizeEvent);

        bool IsMaximized() const { return m_isMaximized; }
        std::string ToString() const override { return std::format("[WindowMaximizeEvent] Is maximized: {}", m_isMaximized); };
    };


}