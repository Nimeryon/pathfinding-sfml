#pragma once
#include <cassert>

#include "Delegate.h"

//////////////////////////////////////////////////
// DelegateListener                             //
//////////////////////////////////////////////////

template <typename ... Args>
DelegateListener<Args...>::DelegateListener(void(*function)(Args... args)) :
	m_function(function)
{}

template <typename... Args>
void DelegateListener<Args...>::Invoke(const Args&... args) const { m_function(args...); }

template <typename ... Args>
bool DelegateListener<Args...>::IsSameFunction(DelegateListenerBase<Args...>* dlb) const
{
	assert(dlb != nullptr);
	auto* dl = dynamic_cast<DelegateListener*>(dlb);
	return dl && dl->m_function == m_function;
}

//////////////////////////////////////////////////
// DelegateListenerMember                       //
//////////////////////////////////////////////////

template <typename I, typename... Args>
DelegateListenerMember<I, Args...>::DelegateListenerMember(I* instance, void(I::* function)(Args... args)) :
	m_instance(instance),
	m_function(function)
{}

template <typename I, typename... Args>
void DelegateListenerMember<I, Args...>::Invoke(const Args&... args) const
{
	if (m_instance) (m_instance->*m_function)(args...);
}

template <typename I, typename... Args>
bool DelegateListenerMember<I, Args...>::IsSameFunction(DelegateListenerBase<Args...>* dlb) const
{
	assert(dlb != nullptr);
	auto* dlm = dynamic_cast<DelegateListenerMember*>(dlb);
	return dlm && dlm->m_instance == m_instance && dlm->m_function == m_function;
}

//////////////////////////////////////////////////
// Delegate                                     //
//////////////////////////////////////////////////

template <typename... Args>
Delegate<Args...>::~Delegate() { Clear(); }

template <typename... Args>
void Delegate<Args...>::Clear()
{
	for (auto* listener : m_listeners)
	{
		delete listener;
		listener = nullptr;
	}
	m_listeners.clear();
}

template <typename... Args>
void Delegate<Args...>::Subscribe(void(*function)(Args... args))
{
	Subscribe(new DelegateListener<Args...>(function));
}
template <typename... Args>
void Delegate<Args...>::UnSubscribe(void(*function)(Args... args))
{
	UnSubscribe(new DelegateListener<Args...>(function));
}
template <typename... Args>
template <typename I>
void Delegate<Args...>::Subscribe(I* instance, void (I::* function)(Args... args))
{
	assert(instance != nullptr);
	Subscribe(new DelegateListenerMember<I, Args...>(instance, function));
}
template <typename... Args>
template <typename I>
void Delegate<Args...>::UnSubscribe(I* instance, void (I::* function)(Args... args))
{
	assert(instance != nullptr);
	UnSubscribe(new DelegateListenerMember<I, Args...>(instance, function));
}

template <typename... Args>
void Delegate<Args...>::operator()(const Args&... args) const
{
	for (auto* listener : m_listeners)
		listener->Invoke(args...);
}

template <typename... Args>
void Delegate<Args...>::Subscribe(DelegateListenerBase<Args...>* dlb)
{
	assert(dlb != nullptr);
	// Test if the listener already in our vector
	for (auto* listener : m_listeners)
		if (listener->IsSameFunction(dlb))
		{
			// Delete listener since it already exist in our vector
			delete dlb;
			dlb = nullptr;
			return;
		}

	m_listeners.push_back(dlb);
}
template <typename... Args>
void Delegate<Args...>::UnSubscribe(DelegateListenerBase<Args...>* dlb)
{
	assert(dlb != nullptr);
	for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it)
	{
		DelegateListenerBase<Args...>* listener = *it;
		if (dlb->IsSameFunction(listener))
		{
			delete listener;
			listener = nullptr;
			m_listeners.erase(it);
			break;
		}
	}
}