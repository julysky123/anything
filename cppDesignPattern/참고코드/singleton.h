#pragma once

#define MAKE_SINGLETON(classname)					        	\
private:											                    	\
	classname() {}										                \
	classname(const classname&) = delete;			       	\
	classname& operator= (const classname&) = delete;	\
public:										                    			\
	static classname& getInstance()				        		\
	{										                        			\
		static classname instance;			          			\
		return instance;								                \
	}													
