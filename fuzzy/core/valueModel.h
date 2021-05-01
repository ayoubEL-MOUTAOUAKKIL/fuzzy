#ifndef VALUEMODEL_H
#define VALUEMODEL_H

namespace core {

	template<typename T>
	class valueModel : public core::Expression<T> {
	public:

		valueModel();
		valueModel(const T&);

		virtual ~valueModel() = default;
		virtual T evaluate()const;
		virtual void setValue(const T&);

	private:
		T value;
	};
	template<typename T>
	valueModel<T>::valueModel() :
		value(0)
	{
	}

	template<typename T>
	valueModel<T>::valueModel(const T& _value) :
		value(_value)
	{
	}

	template<typename T>
	void valueModel<T>::setValue(const T& _value) {
		value = _value;
	}

	template<typename T>
	T valueModel<T>::evaluate()const{
		return value;
	}
}




#endif
