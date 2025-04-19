const express = require('express');
const path = require('path');
const http = require('http');
const net = require('net');
const WebSocket = require('ws');

const app = express();
const PORT = 3000;

// Serve frontend (e.g. index.html + main.js)
app.use(express.static(path.join(__dirname, 'public')));

// Create HTTP server
const server = http.createServer(app);

// Create WebSocket server
const wss = new WebSocket.Server({ server });

// Maintain list of connected clients
const clients = new Set();

// TCP client to the backend (STM32 C++ TCP server)
const tcpClient = new net.Socket();
tcpClient.connect(5555, '127.0.0.1', () => {
  console.log('🔌 Connected to STM32 backend');
});

// Forward TCP data → all WebSocket clients
tcpClient.on('data', (data) => {
  const message = data.toString().trim();
  console.log('📥 From STM32:', message);

  for (const client of clients) {
    if (client.readyState === WebSocket.OPEN) {
      client.send(message);
    }
  }
});

// WebSocket connection handler
wss.on('connection', (ws) => {
  console.log('🌐 Web client connected');
  clients.add(ws);

  ws.on('message', (msg) => {
    console.log('➡️ Command from web:', msg);
    tcpClient.write(msg + '\r\n');
  });

  ws.on('close', () => {
    clients.delete(ws);
    console.log('❌ Web client disconnected');
  });

  ws.on('error', (err) => {
    console.error('WebSocket error:', err.message);
  });
});

// Handle TCP client errors
tcpClient.on('error', (err) => {
  console.error('TCP connection error:', err.message);
});

// Start server
server.listen(PORT, () => {
  console.log(`🚀 Web interface running at http://localhost:${PORT}`);
});
