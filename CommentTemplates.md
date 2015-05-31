**Header File Template**
```
///////////////////////////////////////////////////////////////////////////////
//  COPYRIGHT (c) 2007 Schweitzer Engineering Laboratories, Pullman, WA
///////////////////////////////////////////////////////////////////////////////
///  @file test.h
///
///  @brief
///  One sentence summary of this file.
///
///  @remarks
///  More detailed description of this file 
///  that could span many sentences.  This would be another sentence.  
///
///  Requirements Specification: <Reference the software requirements
///                               specification(s)>
///
///  Design Description: <Reference the software design description(s)>
///
///////////////////////////////////////////////////////////////////////////////

#ifndef _TEST_H_
#define _TEST_H_
```

**Class Template**

```

   ///////////////////////////////////////////////////////////////////////////////
   ///  @class Test
   ///
   ///  @brief 
   ///  One sentence summary description of the class
   ///
   ///  @remarks
   ///  More detailed description providing needed information or more class 
   ///   explanations.
   ///////////////////////////////////////////////////////////////////////////////
   class Test
   {
      public:
```

**Enum Template**

```
   /// One line summary of Enum.
   /// More detailed enum description. 
   enum TEnum 
   { 
      TVal1, ///< Enum value TVal1.
      TVal2, ///< Enum value TVal2.
      TVal3  ///< Enum value TVal3.
   };

   /// Enum pointer.
   /// Details. 
   TEnum *enumPtr;
   
   /// Enum variable. 
   /// Details. More Details.
   /// Most Details. 
   TEnum enumVar;  
```

**Constructor/Destructor Template**

```
   /// A constructor.
   ///
   /// A more elaborate description of the constructor.
   Test(void);

   /// A destructor.
   ///
   /// A more elaborate description of the destructor.
      ~Test(void);
```

**Normal Function Template**

```
   /////////////////////////////////////////////////////////////////////////
   /// A normal member taking two arguments and returning an integer value.
   ///
   ///  INPUTS:
   ///  @param a an integer argument
   ///  @param s a constant character pointer.
   ///
   ///  OUTPUTS:
   ///   none
   ///  
   ///  @return The test results
   ///  @see Test(), ~Test(), testMeToo() and publicVar()
   ///   
   ///  @remarks
   ///  For any more detailed description
   /////////////////////////////////////////////////////////////////////////
   INT32 testMe(INT32 a, char const *s);
```

**Virtual Function Template**

```
   /////////////////////////////////////////////////////////////////////////
   ///  public virtual 
   ///
   ///  @see testMe()
   ///  
   ///  INPUTS:
   ///  @param c1 the first argument.
   ///
   ///  OUTPUTS:
   ///  @param c2 the second argument.
   ///
   ///  @remarks
   ///  For any more detailed description
   //////////////////////////////////////////////////////////////////////////// 
   virtual void testMeToo(char c1,char c2) = 0;
```

**Public variable Template**

```
/// A public variable with no detailed description.
   INT32 publicVar;
```

**Function Variable Template**

```
   /// A function variable.
   ///
   ///  Details.
   ///
   INT32 (*handler)(INT32 a, INT32 b);
```

**Private Function Template**

```
private:
   ///////////////////////////////////////////////////////////////////////
   /// A Private function.
   ///
   /// This is private!
   ///////////////////////////////////////////////////////////////////////
   INT32 private_func(INT32 a);
```

**Private Variable Template**

```
/// A private variable
   INT32 private_variable;
```

**End Header File Template**

```
};
#endif // #define _TEST_H_
```

**Source Code Template**

```
///////////////////////////////////////////////////////////////////////////////
//   COPYRIGHT (c) 2007 Schweitzer Engineering Laboratories, Pullman, WA
///////////////////////////////////////////////////////////////////////////////
///  @file test.cpp
///
///  @brief
///  Summary description of this
///  
///  @remarks
///  More detailed description of this 
///  file that could span many sentences.  This would be another sentence.
///
///  Requirements Specification: <Reference the software requirements 
///                              specification(s)>
///
///  Design Description: <Reference the software design description(s)>
////////////////////////////////////////////////////////////////////////////////
```

**Public Function Template**

```
////////////////////////////////////////////////////////////////////////////////
///  public \b convert_int_to_string
///  
///  @brief
///  An integer to string conversion function
///
///  INPUTS:
///  @param some_int an integer argument.
///  @param some_string a constant character pointer.
///
///  OUTPUTS:
///   none
///
///  @return success(1), or failure(0)
///  
///  @remarks
///  For any more detailed description
////////////////////////////////////////////////////////////////////////////////  
INT32 convert_int_to_string(INT32 some_int, char const *some_string);
```