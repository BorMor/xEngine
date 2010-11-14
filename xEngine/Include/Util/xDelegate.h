#pragma once

struct xDelegateType
{
	enum Enum
    {
		Function,
		Method
    };
};

template <typename F>
class xDelegate;

template <typename R>
class xDelegate< R() >
{
private:
	typedef xDelegate< R() > Delegate;

	class Impl
	{
	public:
		virtual xDelegateType::Enum Type() const = 0;
		virtual R Invoke() = 0;
		virtual bool Equal(const Delegate&) const = 0;
	};

	class Function : public Impl
	{
		typedef R(*FUNCTION_TYPE)();
	public:
		Function(FUNCTION_TYPE function)
			: mFunction(function)
		{
		}

		xDelegateType::Enum Type() const
		{
			return xDelegateType::Function;
		}

		R Invoke()
		{
			return mFunction();
		}

		bool Equal(const Delegate& other) const
		{
			if (Type() != other.mImpl->Type())
				return false;
			Function* function = static_cast<Function*>((Impl*)other.mImpl);
			return mFunction == function->mFunction;
		}
	protected:
		FUNCTION_TYPE	mFunction;
	};

	template<class CLASS_TYPE>
	class Method : public Impl
	{
		typedef R (CLASS_TYPE::*METHOD_TYPE)();
	public:
		Method(CLASS_TYPE* instance, METHOD_TYPE method)
			: mInstance(instance), mMethod(method)
		{
		}

		xDelegateType::Enum Type() const
		{
			return xDelegateType::Method;
		}

		R Invoke()
		{
			return (mInstance->*mMethod)();
		}

		bool Equal(const Delegate& other) const
		{
			if (Type() != other.mImpl->Type())
				return false;

			Method<CLASS_TYPE>* method = static_cast<Method<CLASS_TYPE>*>((Impl*)other.mImpl);
			return mInstance == method->mInstance && mMethod == method->mMethod;
		}
	protected:
		CLASS_TYPE*	mInstance;
		METHOD_TYPE	mMethod;
	};
public:
	template <typename FUNCTION_TYPE>
	xDelegate(FUNCTION_TYPE function)
	{
		mImpl = new Function(function);
	}

	template <class CLASS_TYPE, typename METHOD_TYPE>
	xDelegate(CLASS_TYPE* instance, METHOD_TYPE method)
	{
		mImpl = new Method<CLASS_TYPE>(instance, method);
	}

	R operator ()()
	{
		return mImpl->Invoke();
	}

	bool operator == (const Delegate& other) const
	{
		return mImpl->Equal(other);
	}

	bool operator != (const Delegate& other) const
	{
		return !mImpl->Equal(other);
	}
protected:
	xSharedPtr<Impl>	mImpl;
};

template <typename R, typename A1>
class xDelegate< R(A1) >
{
private:
	typedef xDelegate< R(A1) > Delegate;

	class Impl
	{
	public:
		virtual xDelegateType::Enum Type() const = 0;
		virtual R Invoke(A1 a1) = 0;
		virtual bool Equal(const Delegate&) const = 0;
	};

	class Function : public Impl
	{
		typedef R(*FUNCTION_TYPE)(A1);
	public:
		Function(FUNCTION_TYPE function)
			: mFunction(function)
		{
		}

		xDelegateType::Enum Type() const
		{
			return xDelegateType::Function;
		}

		R Invoke(A1 a1)
		{
			return mFunction(a1);
		}

		bool Equal(const Delegate& other) const
		{
			if (Type() != other.mImpl->Type())
				return false;
			Function* function = static_cast<Function*>((Impl*)other.mImpl);
			return mFunction == function->mFunction;
		}
	protected:
		FUNCTION_TYPE	mFunction;
	};

	template<class CLASS_TYPE>
	class Method : public Impl
	{
		typedef R (CLASS_TYPE::*METHOD_TYPE)(A1);
	public:
		Method(CLASS_TYPE* instance, METHOD_TYPE method)
			: mInstance(instance), mMethod(method)
		{
		}

		xDelegateType::Enum Type() const
		{
			return xDelegateType::Method;
		}

		R Invoke(A1 a1)
		{
			return (mInstance->*mMethod)(a1);
		}

		bool Equal(const Delegate& other) const
		{
			if (Type() != other.mImpl->Type())
				return false;

			Method<CLASS_TYPE>* method = static_cast<Method<CLASS_TYPE>*>((Impl*)other.mImpl);
			return mInstance == method->mInstance && mMethod == method->mMethod;
		}
	protected:
		CLASS_TYPE*	mInstance;
		METHOD_TYPE	mMethod;
	};
public:
	template <typename FUNCTION_TYPE>
	xDelegate(FUNCTION_TYPE function)
	{
		mImpl = new Function(function);
	}

	template <class CLASS_TYPE, typename METHOD_TYPE>
	xDelegate(CLASS_TYPE* instance, METHOD_TYPE method)
	{
		mImpl = new Method<CLASS_TYPE>(instance, method);
	}

	R operator ()(A1 a1)
	{
		return mImpl->Invoke(a1);
	}

	bool operator == (const Delegate& other) const
	{
		return mImpl->Equal(other);
	}

	bool operator != (const Delegate& other) const
	{
		return !mImpl->Equal(other);
	}
protected:
	xSharedPtr<Impl>	mImpl;
};

template <typename R, typename A1, typename A2>
class xDelegate< R(A1, A2) >
{
private:
	typedef xDelegate< R(A1, A2) > Delegate;

	class Impl
	{
	public:
		virtual xDelegateType::Enum Type() const = 0;
		virtual R Invoke(A1 a1, A2 a2) = 0;
		virtual bool Equal(const Delegate&) const = 0;
	};

	class Function : public Impl
	{
		typedef R(*FUNCTION_TYPE)(A1, A2);
	public:
		Function(FUNCTION_TYPE function)
			: mFunction(function)
		{
		}

		xDelegateType::Enum Type() const
		{
			return xDelegateType::Function;
		}

		R Invoke(A1 a1, A2 a2)
		{
			return mFunction(a1, a2);
		}

		bool Equal(const Delegate& other) const
		{
			if (Type() != other.mImpl->Type())
				return false;
			Function* function = static_cast<Function*>((Impl*)other.mImpl);
			return mFunction == function->mFunction;
		}
	protected:
		FUNCTION_TYPE	mFunction;
	};

	template<class CLASS_TYPE>
	class Method : public Impl
	{
		typedef R (CLASS_TYPE::*METHOD_TYPE)(A1, A2);
	public:
		Method(CLASS_TYPE* instance, METHOD_TYPE method)
			: mInstance(instance), mMethod(method)
		{
		}

		xDelegateType::Enum Type() const
		{
			return xDelegateType::Method;
		}

		R Invoke(A1 a1, A2 a2)
		{
			return (mInstance->*mMethod)(a1, a2);
		}

		bool Equal(const Delegate& other) const
		{
			if (Type() != other.mImpl->Type())
				return false;

			Method<CLASS_TYPE>* method = static_cast<Method<CLASS_TYPE>*>((Impl*)other.mImpl);
			return mInstance == method->mInstance && mMethod == method->mMethod;
		}
	protected:
		CLASS_TYPE*	mInstance;
		METHOD_TYPE	mMethod;
	};
public:
	template <typename FUNCTION_TYPE>
	xDelegate(FUNCTION_TYPE function)
	{
		mImpl = new Function(function);
	}

	template <class CLASS_TYPE, typename METHOD_TYPE>
	xDelegate(CLASS_TYPE* instance, METHOD_TYPE method)
	{
		mImpl = new Method<CLASS_TYPE>(instance, method);
	}

	R operator ()(A1 a1, A2 a2)
	{
		return mImpl->Invoke(a1, a2);
	}

	bool operator == (const Delegate& other) const
	{
		return mImpl->Equal(other);
	}

	bool operator != (const Delegate& other) const
	{
		return !mImpl->Equal(other);
	}
protected:
	xSharedPtr<Impl>	mImpl;
};

template <typename R, typename A1, typename A2, typename A3>
class xDelegate< R(A1, A2, A3) >
{
private:
	typedef xDelegate< R(A1, A2, A3) > Delegate;

	class Impl
	{
	public:
		virtual xDelegateType::Enum Type() const = 0;
		virtual R Invoke(A1 a1, A2 a2, A3 a3) = 0;
		virtual bool Equal(const Delegate&) const = 0;
	};

	class Function : public Impl
	{
		typedef R(*FUNCTION_TYPE)(A1, A2, A3);
	public:
		Function(FUNCTION_TYPE function)
			: mFunction(function)
		{
		}

		xDelegateType::Enum Type() const
		{
			return xDelegateType::Function;
		}

		R Invoke(A1 a1, A2 a2, A3 a3)
		{
			return mFunction(a1, a2, a3);
		}

		bool Equal(const Delegate& other) const
		{
			if (Type() != other.mImpl->Type())
				return false;
			Function* function = static_cast<Function*>((Impl*)other.mImpl);
			return mFunction == function->mFunction;
		}
	protected:
		FUNCTION_TYPE	mFunction;
	};

	template<class CLASS_TYPE>
	class Method : public Impl
	{
		typedef R (CLASS_TYPE::*METHOD_TYPE)(A1, A2, A3);
	public:
		Method(CLASS_TYPE* instance, METHOD_TYPE method)
			: mInstance(instance), mMethod(method)
		{
		}

		xDelegateType::Enum Type() const
		{
			return xDelegateType::Method;
		}

		R Invoke(A1 a1, A2 a2, A3 a3)
		{
			return (mInstance->*mMethod)(a1, a2, a3);
		}

		bool Equal(const Delegate& other) const
		{
			if (Type() != other.mImpl->Type())
				return false;

			Method<CLASS_TYPE>* method = static_cast<Method<CLASS_TYPE>*>((Impl*)other.mImpl);
			return mInstance == method->mInstance && mMethod == method->mMethod;
		}
	protected:
		CLASS_TYPE*	mInstance;
		METHOD_TYPE	mMethod;
	};
public:
	template <typename FUNCTION_TYPE>
	xDelegate(FUNCTION_TYPE function)
	{
		mImpl = new Function(function);
	}

	template <class CLASS_TYPE, typename METHOD_TYPE>
	xDelegate(CLASS_TYPE* instance, METHOD_TYPE method)
	{
		mImpl = new Method<CLASS_TYPE>(instance, method);
	}

	R operator ()(A1 a1, A2 a2, A3 a3)
	{
		return mImpl->Invoke(a1, a2, a3);
	}

	bool operator == (const Delegate& other) const
	{
		return mImpl->Equal(other);
	}

	bool operator != (const Delegate& other) const
	{
		return !mImpl->Equal(other);
	}
protected:
	xSharedPtr<Impl>	mImpl;
};
