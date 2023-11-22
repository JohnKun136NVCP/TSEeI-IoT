var xhr = new XMLHttpRequest();
xhr.open('GET', 'datos.php', true);
    xhr.onload = function () {
        if (xhr.status >= 200 && xhr.status < 300) {
            var data = JSON.parse(xhr.responseText);
            // Prepara los datos para el buen Chart.js
            var labels = data.map(function (item) {
                return item.time;
            });

            var values = data.map(function (item) {
                return item.packlen;
            });

            // Configura el gráfico con Chart.js
            var ctx = document.getElementById('myChart').getContext('2d');
            var myChart = new Chart(ctx, {
                type: 'line',
                data: {
                    labels: labels,
                    datasets: [{
                        label: 'Tamaño del paquete a través del tiempo',
                        data: values,
                        borderWidth: 1
                    }]
                }
            });
        // Ajustando el tamaño del contenedor
        ctx.canvas.parentNode.style.width = '60%';  // Ajusta el ancho al 60% del contenedor padre, porque sino se ve bien pegado todo.
        ctx.canvas.parentNode.style.margin = 'auto';  // Centrando el contenedor
        }
    };
    xhr.send();
