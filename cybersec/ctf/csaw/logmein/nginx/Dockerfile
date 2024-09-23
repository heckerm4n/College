FROM nginx@sha256:0f04e4f646a3f14bf31d8bc8d885b6c951fdcf42589d06845f64d18aec6a3c4d

ARG WEBAPP_HOST
ARG WEBAPP_PORT

COPY nginx-default.conf /etc/nginx/templates/default.conf.template

EXPOSE 9996


CMD ["nginx", "-g", "daemon off;"]
