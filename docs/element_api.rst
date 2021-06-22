.. element_api:

Element API
===========

This page documents the API convention for accessing parameters of ADM element
classes. Element classes like :cpp:class:`AudioBlockFormatObjects` contain many
parameters, each with different types (thanks to using named types). These
parameters can be accessed through a common set of templated and overloaded
methods defined on elements. Compared to standard accessor methods, this makes
it easy to write templates which handle parameters generically.

.. note::
   The classes listed on this page do not actually exist, they just serve to
   show the API on element classes themselves.

The set of methods which may be defined for each parameter of type
``Parameter`` are shown below:

.. cpp:class:: adm::Element

   .. cpp:function:: template<typename Parameter> Parameter get()

      Get the value of a parameter. If the parameter has no default value and
      has not been set then an error is raised. This precondition can be checked
      by calling :cpp:func:`has`.

   .. cpp:function:: void set(Parameter parameter)

      Set the value of a parameter.

   .. cpp:function:: template<typename Parameter> bool has<Parameter>()

      Returns true if the ADM parameter is set or has a default value, and
      therefore :cpp:func:`get` will not raise an error.

   .. cpp:function:: template<typename Parameter> void unset<Parameter>()

      Resets the parameter to its default value if it has one, otherwise removes
      it from the element.

   .. cpp:function:: template<typename Parameter> bool isDefault<Parameter>()

      Returns true if the parameter has a default and has been set; this is
      useful to see if the default value was specified explicitly in the
      ADM XML, and is used to control whether default values are written out in
      XML.

   .. cpp:function:: bool add(Parameter parameter)

      For parameters with multiple values, add a new value, ensuring uniqueness.
      Returns true if the parameter was added, or false if it already had a
      parameter with this value.

   .. cpp:function:: void remove(Parameter parameter)

      For parameters with multiple values, remove the provided value if present.

These methods are implemented in some common patterns for parameters which
behave in different ways:

.. cpp:class:: template<typename T> adm::RequiredParameter

   Required parameters are those which must always be present in the element
   according to the ADM standard.

   .. cpp:function:: template<> bool get<T>()

      see :cpp:func:`Element::get`

   .. cpp:function:: void set(T)

      see :cpp:func:`Element::set`

   .. cpp:function:: template<> bool has<T>()

      always returns true

.. cpp:class:: template<typename T> adm::OptionalParameter

   Optional parameters may or may not be specified.

   .. cpp:function:: template<> bool get<T>()

      see :cpp:func:`Element::get`

   .. cpp:function:: void set(T)

      see :cpp:func:`Element::set`

   .. cpp:function:: template<> bool has<T>()

      see :cpp:func:`Element::has`

   .. cpp:function:: template<> void unset<T>()

      see :cpp:func:`Element::unset`

   .. cpp:function:: template<> bool isDefault<T>()

      always returns false

.. cpp:class:: template<typename T> adm::DefaultParameter

   Default parameters may or may not be specified, but have a default defined
   by the standard. The default is assumed by something consuming ADM, so will
   only be written out by libadm if :cpp:func:`set` explicitly.

   .. cpp:function:: template<> bool get<T>()

      see :cpp:func:`Element::get`

   .. cpp:function:: void set(T)

      see :cpp:func:`Element::set`

   .. cpp:function:: template<> bool has<T>()

      see :cpp:func:`Element::has`

   .. cpp:function:: template<> void unset<T>()

      see :cpp:func:`Element::unset`

   .. cpp:function:: template<> bool isDefault<T>()

      see :cpp:func:`Element::isDefault`

.. cpp:class:: template<typename VectorT> adm::VectorParameter

   Vector parameters have multiple values, and some concept of equality, defined
   by :cpp:class:`detail::ParameterCompare<T>`

   ``get`` and ``set`` methods get and set a :cpp:class:`std::vector\<T>`
   holding the parameters, while ``add`` and ``remove`` add and remove
   individual values.

   .. cpp:type:: T = VectorT::value_type

   .. cpp:function:: template<> bool get<VectorT>()

      get a vector of parameters.

   .. cpp:function:: void set(VectorT)

      Set a vector of parameters.

   .. cpp:function:: template<> bool has<VectorT>()

      Have any parameters been set?

   .. cpp:function:: template<> void unset<VectorT>()

      Clear the list of parameters.

   .. cpp:function:: template<> bool isDefault<VectorT>()

      Always returns false.

   .. cpp:function:: bool add(T)

      Add a new value, ensuring uniqueness. Returns true if the parameter was
      added, or false if it already had a parameter with this value.

   .. cpp:function:: void remove(T)

      Remove a parameter from the list.
