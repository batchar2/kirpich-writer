 [![](https://github.com/batchar2/kirpich-writer/workflows/test/badge.svg)](https://github.com/batchar2/kirpich-writer/)

### Медиасервер для систем видеонаблюдения

Пишет архивы для камер видеонаблюдения. Управление реализовано через JSON-RPC АПИ

#### Сборка

```
docker build -t kirpich .
```

#### Запуск

```
docker run -p 5000:5000 -ti kirpich
```




#### Команды

Сервер реализует JSON-RPC методы для работы с камерами: start, stop, pause


###### Начать запись архива для камеры:
```
curl \
    --header "Content-Type: application/json" \
    --request POST \
    --data '{ "method": "start", "params": {"id": "100500", "rtsp_uri": "rtsp://stream.studio360.tv:554/nw/nw_576p"} }' \
    'http://127.0.0.1:5000/api/json-rpc/'
```

###### Приостановить запись архива:
```
curl \
    --header "Content-Type: application/json" \
    --request POST \
    --data '{ "method": "pause", "params": {"id": "100500"} }' \
    'http://127.0.0.1:5000/api/json-rpc/'
```


###### Остановить и удалить все записанные данные:
```
curl \
    --header "Content-Type: application/json" \
    --request POST \
    --data '{ "method": "stop", "params": {"id": "100500"} }' \
    'http://127.0.0.1:5000/api/json-rpc/'
```
