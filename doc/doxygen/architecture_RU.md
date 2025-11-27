# Архитектура glTF 2.0 loader #

## Общие положения для классов glTF 2.0 ##

Для всех классов объектов glTF 2.0 работают общие положения архитектуры и поведения.

Объекты класса glTF подразделяются на три типа:
- простые объекты, не имеющие имени и специальных секций. Они, как правило, являются подклассами других классов;
- базовые объекты. Они отличаются от простых объектов наличием секций `extensions` и `extras`. Поскольку стандарт glTF 2.0 только рекомендует использование в качестве этих секций объектов JSON, то их инкапсуляция делегируется классу [GLTFObject](#gltfloader::GLTFObject). Следовательно, все классы для описания данных объектов должны наследоваться от [GLTFObject](#gltfloader::GLTFObject);
- именованные объекты. Эти объекты имеют поле name, содержащее строку с именем самого объекта. Инкапсуляция этого имени содержится в классе [GLTFNamedObject](#gltfloader::GLTFNamedObject), который предоставляет способ получения этой строки.

Каждый класс, наследуемый от [GLTFObject](#gltfloader::GLTFObject) или [GLTFNamedObject](#gltfloader::GLTFNamedObject), должен реализовать определенные методы.

Виртуальный деструктор.
~~~cpp
virtual ~GLTFObject ();
virtual ~GLTFNamedObject ();
~~~

Каждый класс, наследуемый от [GLTFObject](#gltfloader::GLTFObject) или [GLTFNamedObject](#gltfloader::GLTFNamedObject), должен иметь конструктор по умолчанию в приватной секции. Реализация данного конструктора должна быть такой, чтобы все поля создаваемого класса были бы проинициализированы максимально безопасно.

Классы, наследуемые от [GLTFObject](#gltfloader::GLTFObject) или [GLTFNamedObject](#gltfloader::GLTFNamedObject), не могут иметь специализированных открытых конструкторов, поскольку создание объекта класса не может быть публичным.

Для создания объектов классов, наследуемых от [GLTFObject](#gltfloader::GLTFObject) или [GLTFNamedObject](#gltfloader::GLTFNamedObject), необходимо воспользоваться следующим фабричным методом:

~~~cpp
class SomeClass : public GLTFObject // или GLTFNamedObject
{
public:
  static std::shared_ptr<SomeClass> create (arguments);
};
~~~

В этом методе `arguments` обозначают необходимое число аргументов, полностью инициализирующих создаваемый объект. При реализации данного метода сперва создается `std::shared_ptr<SomeClass>` при помощи приватного конструктора по умолчанию. Затем следует проверка всех аргументов на соответствие пункту стандарта glTF 2.0. Если ни в одном аргументе не выявлено нарушений, то выполняется инициализация, и метод возвращает созданный `std::shared_ptr<SomeClass>`. Если в процессе проверки выявлено несоответствие, возвращается `nullptr`. Таким образом, для создания объекта класса `SomeClass` в этом примере необходимо выполнить такой код:

~~~cpp
std::shared_ptr<SomeClass> obj = SomeClass::create(arguments);
if (obj == nullptr)
  {
    // Обработать ошибку
  }
~~~

При таком способе инициализации указатель на создаваемый объект всегда либо абсолютно соответствует спецификации, либо равен `nullptr`.

Для аргументов фабричного метода и полей класса существует набор правил, позволяющий создать однородную архитектуру всех классов, и предоставить удобный механизм проверки созданного объекта.

Если соответствующе поле объекта glTF 2.0 имеет тип - JSON объект, для него должен быть создан отдельный простой класс (в примере - `FieldClass`). В качестве поля в таком случае выступает поле типа `std::shared_ptr<FieldClass>`. В фабричном методе используется константный аргумент типа `const std::shared_ptr<FieldClass>&`. Конструирование встроенного объекта выполняется "на месте".

Если поле является простой величиной (типы number, string, true, false в JSON), и при этом является обязательным или имеет значение по умолчанию, он добавляется в виде соответствующего поля в создаваемый класс, принимая наиболее близкий тип. В фабричном методе аргумент добавляется обязательно. В случае установленного значения по умолчанию, это значение передается в фабричный метод, а аргумент перемещается в секцию необязательных аргументов.

Если поле является простой величиной, но при этом не является обязательным полем и не имеет значения по умолчанию (например, цвет материала может задаваться значением или текстурой. В случае текстуры, цвет не указывается совсем), тип должен быть обернут в `std::optional`. Также следует обернуть в `std::optional` и аргумент фабричного метода. В случае, если элемент не найден в glTF 2.0 файле, в качестве аргумента передается `nullopt`, обозначая отсутствие значения в данном gltf-файле.

Для каждого поля в объекте должен быть предусмотрен getter.

## Класс GLTFPBRMetallicRoughness ##

Согласно спецификации glTF 2.0 5.22 объект pbrMetallicRoughness включает в себя
следующие поля:

 Наименование | Тип | Обязательный атрибут | Значение по умолчанию
:-------------------------:|:------:|:--------------------:|:---------------------:
`baseColorFactor` | array  | Нет | `[1, 1, 1, 1]`
`baseColorTexture` | object | Нет | -
`metallicFactor` | number | Нет | 1,0
`roughnessFactor` | number | Нет | 1,0
`metallicRoughnessTexture` | object | Нет | -
`extensions` | object | Нет | -
`extras` | object | Нет | -

Как мы видим, есть дополнительные поля `extensions` и `extras`, которые в архитектуре загрузчика инкапсулированы в класс [GLTFObject](#gltfloader::GLTFObject). Это означает, что класс [GLTFPBRMetallicRoughness](#gltfloader::GLTFPBRMetallicRoughness) наследуется от [GLTFObject](#gltfloader::GLTFObject). Описание класса [GLTFObject](#gltfloader::GLTFObject) можно найти в [соответствующем разделе](#класс-gltfobject).

Интерфейс класса приведен ниже.

~~~cpp
class GLTFPBRMetallicRoughness : public GLTFObject
{
private:
  std::array<float, 4> m_base_color_factor;
  std::shared_ptr<GLTFTextureInfo> m_base_color_texture;
  float m_metallic_factor;
  float m_roughness_factor;
  std::shared_ptr<GLTFTextureInfo> m_metallic_roughness_texture;

  GLTFPBRMetallicRoughness ();

public:
  GLTFPBRMetallicRoughness (const GLTFPBRMetallicRoughness &) = delete;
  virtual ~GLTFPBRMetallicRoughness () {}

  const std::array<float, 4> &base_color_factor () const;
  const std::shared_ptr<GLTFTextureInfo> &base_color_texture () const;
  float metallic_factor () const;
  float roughness_factor () const;
  const std::shared_ptr<GLTFTextureInfo> &metallic_roughness_texture () const;

  /**
   * \brief Fabric creation method for GLTFPBRMetallicRoughness class
   */
  static std::shared_ptr<GLTFPBRMetallicRoughness>
  create (const std::array<float, 4> &base_color_factor
          = { 1.0f, 1.0f, 1.0f, 1.0f },
          const std::shared_ptr<GLTFTextureInfo> &base_color_texture = nullptr,
          float metallic_factor = 1.0f, float roughness_factor = 1.0f,
          const std::shared_ptr<GLTFTextureInfo> &metallic_roughness_texture
          = nullptr);
};
~~~

Стандарт glTF 2.0 определяет вектор масштабных коэффициентов для базового цвета baseColorFactor, описываемый `std::array<float, 4>` типом. Его значение всегда присутствует в объекте [GLTFPBRMetallicRoughness](#gltfloader::GLTFPBRMetallicRoughness) и принимает значение по умолчанию, если отсутствует в аргументах. Поля `metallicFactor` и `roughnessFactor` также присутствуют в объектах [GLTFPBRMetallicRoughness](#gltfloader::GLTFPBRMetallicRoughness) всегда, инициализируясь при необходимости значениями по умолчанию. Текстуры `baseColorTexture` и `metallicRoughnessTexture` являются объектами JSON со структурой `textureInfo`, описанной в подразделе 5.30 стандарта. Они не являются обязательными. Но в отличие от простых значений, не передаются в фабричный метод по значению. Вместо этого используются умные указатели. Если какой-либо из этих аргументов должен быть опущен, достаточно передать `nullptr`.

Если поле [m_base_color_texture](#gltfloader::GLTFPBRMetallicRoughness::m_base_color_texture) или [m_metallic_roughness_texture](#gltfloader::GLTFPBRMetallicRoughness::m_metallic_roughness_texture) в объекте [GLTFPBRMetallicRoughness](#gltfloader::GLTFPBRMetallicRoughness), то согласно спецификации, необходимо использовать текстуру с семплами, инициализированными числом 1,0. Однако такая операция выходит за рамки загрузчика.
