#pragma once
#include <vector>

template <typename ...Args>
class DelegateListenerBase abstract
{
public:
	virtual ~DelegateListenerBase() = default;

	virtual void Invoke(const Args& ...args) const = 0;

	virtual bool IsSameFunction(DelegateListenerBase* dlb) const = 0;
};

/**
 * \brief Class for storing a function and do some testing on it
 * \tparam Args List of every parameters types
 */
template <typename ...Args>
class DelegateListener final : public DelegateListenerBase<Args...>
{
public:
	DelegateListener(void(*function)(Args... args));

	void Invoke(const Args& ...args) const override;

	bool IsSameFunction(DelegateListenerBase<Args...>* dlb) const override;

private:
	void(*m_function)(Args... args);
};

/**
 * \brief Class for storing a member function and do some testing on it
 * \tparam Args List of every parameters types
 */
template <typename I, typename ...Args>
class DelegateListenerMember final : public DelegateListenerBase<Args...>
{
public:
	DelegateListenerMember(I* instance, void(I::* function)(Args... args));

	void Invoke(const Args& ...args) const override;

	bool IsSameFunction(DelegateListenerBase<Args...>* dlb) const override;

private:
	I* m_instance;
	void(I::* m_function)(Args... args);
};

/**
 * \brief Delegate implementation, store a list of DelegateListener
 * that are called on () operator
 * \tparam Args List of every parameters types
 */
template <typename ...Args>
class Delegate final
{
public:
	~Delegate();

	void Subscribe(void(*function)(Args... args));
	void UnSubscribe(void(*function)(Args... args));
	template <typename I>
	void Subscribe(I* instance, void(I::* function)(Args... args));
	template <typename I>
	void UnSubscribe(I* instance, void(I::* function)(Args... args));
	void Clear();

	void operator()(const Args& ...args) const;

private:
	std::vector<DelegateListenerBase<Args...>*> m_listeners;

	void Subscribe(DelegateListenerBase<Args...>* dlb);
	void UnSubscribe(DelegateListenerBase<Args...>* dlb);

public:
	Delegate& operator=(const Delegate&) = delete;
};

#include "Delegate.hxx"