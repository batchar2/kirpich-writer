 [![](https://github.com/batchar2/kirpich-writer/workflows/test/badge.svg)](https://github.com/batchar2/kirpich-writer/)

### Медиасервер для систем видеонаблюдения

#### Сборка



```
docker build -t kirpich .
```

#### Запуск

```
docker run -p 5000:5000 -ti kirpich
```