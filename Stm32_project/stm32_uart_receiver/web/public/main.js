const socket = new WebSocket('ws://localhost:3000');

// UI Elements
const statusEl = document.getElementById('connectionStatus');
const logOutput = document.getElementById('logOutput');
const commandTypeSelect = document.getElementById('commandType');
const commandFieldsDiv = document.getElementById('commandFields');
const commandForm = document.getElementById('commandForm');
const dataTable = document.getElementById('dataTable');
const dataTableBody = dataTable.querySelector('tbody');
const dataSection = document.getElementById('dataSection');

// chart.js elements
const tempChart = createChart('tempChart', 'Temperature (°C)');
const humidityChart = createChart('humidityChart', 'Humidity (%)');
const voltageChart = createChart('voltageChart', 'Voltage (V)');
const lightChart = createChart('lightChart', 'Light (%)');

// update chart
function updateChart(chart, label, value) {
    chart.data.labels.push(label);
    chart.data.datasets[0].data.push(value);
    if (chart.data.labels.length > 30) {
        chart.data.labels.shift();
        chart.data.datasets[0].data.shift();
    }
    chart.update();
}

// Chart setup
function createChart(canvasId, label) {
    const ctx = document.getElementById(canvasId).getContext('2d');
    return new Chart(ctx, {
        type: 'line',
        data: {
            labels: [],
            datasets: [{
                label,
                data: [],
                fill: false,
                borderWidth: 2,
                tension: 0.3
            }]
        },
        options: {
            scales: {
                y: { beginAtZero: false },
                x: { display: false }
            }
        }
    });
}

// websocket events
socket.onopen = () => {
    statusEl.classList.remove('status-offline');
    statusEl.classList.add('status-online');
};

socket.onclose = () => {
    statusEl.classList.remove('status-online');
    statusEl.classList.add('status-offline');
};

socket.onerror = (err) => {
    console.error('WebSocket error:', err);
    statusEl.classList.remove('status-online');
    statusEl.classList.add('status-offline');
};

socket.onmessage = (event) => {
    const message = event.data.trim();

    const div = document.createElement('div');
    div.textContent = message;
    logOutput.appendChild(div);
    logOutput.scrollTop = logOutput.scrollHeight;

    if (message.startsWith('DATA:')) {
        const line = message.replace('DATA: ', '');
        const [timestamp, tempStr, humidStr, voltStr, lightStr] = line.split(',');

        dataTableBody.innerHTML += `
          <tr>
            <td>${timestamp.trim()}</td>
            <td>${tempStr.trim()}</td>
            <td>${humidStr.trim()}</td>
            <td>${voltStr.trim()}</td>
            <td>${lightStr.trim()}</td>
          </tr>
        `;
        dataSection.style.display = 'block';
    }

    if (message.startsWith('LOGGED:')) {
        const [, log] = message.split('LOGGED:');
        const [timestamp, tempStr, humidStr, voltStr, lightStr] = log.split(',');

        const temp = parseFloat(tempStr);
        const humidity = parseFloat(humidStr);
        const voltage = parseFloat(voltStr);
        const light = parseFloat(lightStr);

        updateChart(tempChart, timestamp, temp);
        updateChart(humidityChart, timestamp, humidity);
        updateChart(voltageChart, timestamp, voltage);
        updateChart(lightChart, timestamp, light);
    }
};

commandTypeSelect.addEventListener('change', () => {
    const selected = commandTypeSelect.value;
    commandFieldsDiv.innerHTML = '';
    dataTableBody.innerHTML = '';
    dataSection.style.display = 'none';

    if (selected === 'setconfig') {
        commandFieldsDiv.innerHTML = `
          <div class="row">
            <div class="col"><input class="form-control" id="temp_min" placeholder="Temp Min"></div>
            <div class="col"><input class="form-control" id="temp_max" placeholder="Temp Max"></div>
          </div>
          <div class="row mt-2">
            <div class="col"><input class="form-control" id="humidity_min" placeholder="Humidity Min"></div>
            <div class="col"><input class="form-control" id="light_min" placeholder="Light Min"></div>
            <div class="col"><input class="form-control" id="voltage_min" placeholder="Voltage Min"></div>
          </div>
        `;
    } else if (selected === 'get') {
        commandFieldsDiv.innerHTML = `
          <label class="form-label mt-2">Start DateTime:</label>
          <input type="datetime-local" class="form-control mb-2" id="start_datetime">
          <label class="form-label">End DateTime:</label>
          <input type="datetime-local" class="form-control" id="end_datetime">
        `;
    } else if (selected === 'custom') {
        commandFieldsDiv.innerHTML = `
          <input type="text" id="customCommand" class="form-control" placeholder="Enter your custom command">
        `;
    }
});

commandForm.addEventListener('submit', (e) => {
    e.preventDefault();
    const selected = commandTypeSelect.value;
    let command = '';

    if (selected === 'setconfig') {
        const tempMin = document.getElementById('temp_min').value;
        const tempMax = document.getElementById('temp_max').value;
        const humidityMin = document.getElementById('humidity_min').value;
        const lightMin = document.getElementById('light_min').value;
        const voltageMin = document.getElementById('voltage_min').value;
        command = `SETCONFIG temp_min=${tempMin} temp_max=${tempMax} humidity_min=${humidityMin} light_min=${lightMin} voltage_min=${voltageMin}`;

    } else if (selected === 'get') {
        const start = document.getElementById('start_datetime').value;
        const end = document.getElementById('end_datetime').value;
        if (start && end) {
            const startFormatted = start.replace('T', ' ') + ':00';
            const endFormatted = end.replace('T', ' ') + ':00';
            command = `GET ${startFormatted} TO ${endFormatted}`;
        }
        dataTableBody.innerHTML = '';
        dataSection.style.display = 'none';
    } else if (selected === 'custom') {
        command = document.getElementById('customCommand').value.trim();
    }

    if (command) {
        socket.send(command);
    }
});
