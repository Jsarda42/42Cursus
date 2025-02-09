FROM python:latest

RUN apt-get update \
    && apt-get install -y libpq-dev gcc postgresql-client curl \
    && python -m pip install Django \
    && python -m pip install psycopg2-binary \
    && python -m pip install python-decouple \
    && python -m pip install requests \
    && python -m pip install Pillow \
    && python -m pip install djangorestframework \
    && python -m pip install djangorestframework-simplejwt \
    && python -m pip install python-dotenv \
    && python -m pip install -U 'channels[daphne]'\
    && python -m pip install channels_redis\
    && python -m pip install faker\
    # && python -m pip install celery\
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

RUN curl -o /wait-for-it.sh https://raw.githubusercontent.com/vishnubob/wait-for-it/master/wait-for-it.sh \
    && chmod +x /wait-for-it.sh

COPY .env /app/.env
COPY django/transcendence /app
COPY django/scripts/wait-for-it.sh /wait-for-it.sh

WORKDIR /app

EXPOSE 8000
EXPOSE 8001


CMD ["bash", "-c", "/wait-for-it.sh postgres:5432 -- python manage.py makemigrations transcendence game && python manage.py migrate && python manage.py clean_room  && python manage.py clean_online && python manage.py runserver 0.0.0.0:8000"]

