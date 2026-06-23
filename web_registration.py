import asyncio
import logging
import os
from aiohttp import web
from server.database import DatabaseManager

logger = logging.getLogger("WebRegistration")

HTML_CONTENT = """<!DOCTYPE html>
<html lang="tr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Wonderland Online - Kayıt Paneli</title>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Outfit:wght@300;400;600;700&display=swap" rel="stylesheet">
    <style>
        :root {
            --bg-color: #080c14;
            --panel-bg: rgba(22, 28, 45, 0.45);
            --border-color: rgba(255, 255, 255, 0.08);
            --text-color: #f3f4f6;
            --text-muted: #9ca3af;
            --accent-cyan: #00f2fe;
            --accent-purple: #9b51e0;
            --accent-green: #10b981;
            --accent-red: #ef4444;
            --accent-gradient: linear-gradient(135deg, #00f2fe 0%, #9b51e0 100%);
            --glass-shadow: 0 8px 32px 0 rgba(0, 0, 0, 0.5);
        }

        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
            font-family: 'Outfit', sans-serif;
            -webkit-font-smoothing: antialiased;
        }

        body {
            background-color: var(--bg-color);
            color: var(--text-color);
            display: flex;
            justify-content: center;
            align-items: center;
            min-height: 100vh;
            overflow-x: hidden;
            background-image: 
                radial-gradient(at 10% 20%, rgba(0, 242, 254, 0.08) 0px, transparent 50%),
                radial-gradient(at 90% 80%, rgba(155, 81, 224, 0.08) 0px, transparent 50%);
            background-attachment: fixed;
        }

        .container {
            width: 100%;
            max-width: 450px;
            padding: 1.5rem;
        }

        .card {
            background: var(--panel-bg);
            border: 1px solid var(--border-color);
            backdrop-filter: blur(20px);
            border-radius: 20px;
            padding: 2.5rem 2rem;
            box-shadow: var(--glass-shadow);
            position: relative;
            overflow: hidden;
            transition: border-color 0.3s;
        }

        .card::before {
            content: '';
            position: absolute;
            top: 0;
            left: 0;
            right: 0;
            height: 4px;
            background: var(--accent-gradient);
        }

        .card:hover {
            border-color: rgba(0, 242, 254, 0.15);
        }

        .header {
            text-align: center;
            margin-bottom: 2rem;
        }

        .header h1 {
            font-size: 2.25rem;
            font-weight: 700;
            background: var(--accent-gradient);
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
            letter-spacing: -0.5px;
            margin-bottom: 0.5rem;
        }

        .header p {
            color: var(--text-muted);
            font-size: 0.95rem;
        }

        .form-group {
            display: flex;
            flex-direction: column;
            gap: 0.5rem;
            margin-bottom: 1.25rem;
        }

        .form-group label {
            font-size: 0.875rem;
            color: var(--text-muted);
            font-weight: 600;
            text-transform: uppercase;
            letter-spacing: 0.05em;
        }

        .input-wrapper {
            position: relative;
        }

        input {
            width: 100%;
            background: rgba(8, 12, 20, 0.6);
            border: 1px solid var(--border-color);
            color: var(--text-color);
            padding: 0.85rem 1.2rem;
            border-radius: 10px;
            font-size: 1rem;
            outline: none;
            transition: border-color 0.3s, box-shadow 0.3s;
        }

        input:focus {
            border-color: var(--accent-cyan);
            box-shadow: 0 0 15px rgba(0, 242, 254, 0.2);
        }

        .btn-submit {
            width: 100%;
            background: var(--accent-gradient);
            color: white;
            border: none;
            padding: 0.9rem;
            border-radius: 10px;
            font-size: 1rem;
            font-weight: 600;
            cursor: pointer;
            transition: opacity 0.3s, transform 0.1s;
            margin-top: 1rem;
            display: flex;
            justify-content: center;
            align-items: center;
            gap: 0.5rem;
        }

        .btn-submit:hover {
            opacity: 0.95;
            box-shadow: 0 0 20px rgba(0, 242, 254, 0.25);
        }

        .btn-submit:active {
            transform: scale(0.98);
        }

        .btn-submit:disabled {
            opacity: 0.5;
            cursor: not-allowed;
            box-shadow: none;
        }

        .alert {
            display: none;
            padding: 1rem;
            border-radius: 10px;
            font-size: 0.9rem;
            margin-bottom: 1.5rem;
            line-height: 1.4;
            border: 1px solid transparent;
        }

        .alert-error {
            background: rgba(239, 68, 68, 0.1);
            color: #fca5a5;
            border-color: rgba(239, 68, 68, 0.2);
        }

        .alert-success {
            background: rgba(16, 185, 129, 0.1);
            color: #a7f3d0;
            border-color: rgba(16, 185, 129, 0.2);
        }

        .spinner {
            width: 18px;
            height: 18px;
            border: 2px solid rgba(255, 255, 255, 0.3);
            border-top-color: white;
            border-radius: 50%;
            animation: spin 0.8s linear infinite;
            display: none;
        }

        @keyframes spin {
            to { transform: rotate(360deg); }
        }

        .footer-text {
            text-align: center;
            font-size: 0.85rem;
            color: var(--text-muted);
            margin-top: 1.5rem;
        }

        .footer-text a {
            color: var(--accent-cyan);
            text-decoration: none;
            transition: color 0.2s;
        }

        .footer-text a:hover {
            color: var(--accent-purple);
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="card">
            <div class="header">
                <h1>Wonderland Online</h1>
                <p>Kayıt Ol & Maceraya Başla</p>
            </div>

            <div id="alert-box" class="alert"></div>

            <form id="register-form" onsubmit="handleRegister(event)">
                <div class="form-group">
                    <label for="username">Kullanıcı Adı</label>
                    <div class="input-wrapper">
                        <input type="text" id="username" required minlength="3" maxlength="15" autocomplete="username" placeholder="Kullanıcı adınızı girin">
                    </div>
                </div>

                <div class="form-group">
                    <label for="password">Şifre</label>
                    <div class="input-wrapper">
                        <input type="password" id="password" required minlength="4" maxlength="20" autocomplete="new-password" placeholder="Şifrenizi girin">
                    </div>
                </div>

                <div class="form-group">
                    <label for="confirm-password">Şifre Tekrar</label>
                    <div class="input-wrapper">
                        <input type="password" id="confirm-password" required minlength="4" maxlength="20" autocomplete="new-password" placeholder="Şifrenizi tekrar girin">
                    </div>
                </div>

                <button type="submit" id="btn-submit" class="btn-submit">
                    <span class="spinner" id="spinner"></span>
                    <span id="btn-text">Hesap Oluştur</span>
                </button>
            </form>

            <div class="footer-text">
                Hesabınız var mı? Oyuna giriş yapıp oynamaya başlayabilirsiniz.
            </div>
        </div>
    </div>

    <script>
        async function handleRegister(event) {
            event.preventDefault();
            
            const usernameInput = document.getElementById('username');
            const passwordInput = document.getElementById('password');
            const confirmInput = document.getElementById('confirm-password');
            
            const alertBox = document.getElementById('alert-box');
            const btnSubmit = document.getElementById('btn-submit');
            const btnText = document.getElementById('btn-text');
            const spinner = document.getElementById('spinner');
            
            const username = usernameInput.value.trim();
            const password = passwordInput.value;
            const confirmPassword = confirmInput.value;
            
            // Basic Client-side validation
            if (password !== confirmPassword) {
                showAlert('Şifreler eşleşmiyor!', 'error');
                return;
            }
            
            if (username.length < 3) {
                showAlert('Kullanıcı adı en az 3 karakter olmalıdır!', 'error');
                return;
            }
            
            // Set loading state
            btnSubmit.disabled = true;
            spinner.style.display = 'inline-block';
            btnText.textContent = 'Kayıt Yapılıyor...';
            alertBox.style.display = 'none';
            
            try {
                const response = await fetch('/api/register', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    body: JSON.stringify({
                        username: username,
                        password: password
                    })
                });
                
                const result = await response.json();
                
                if (response.ok && result.status === 'success') {
                    showAlert('Hesap başarıyla oluşturuldu! Oyuna giriş yapabilirsiniz.', 'success');
                    usernameInput.value = '';
                    passwordInput.value = '';
                    confirmInput.value = '';
                } else {
                    showAlert(result.message || 'Kayıt sırasında bir hata oluştu!', 'error');
                }
            } catch (error) {
                showAlert('Sunucuya bağlanılamadı. Lütfen daha sonra tekrar deneyin.', 'error');
            } finally {
                btnSubmit.disabled = false;
                spinner.style.display = 'none';
                btnText.textContent = 'Hesap Oluştur';
            }
        }
        
        function showAlert(message, type) {
            const alertBox = document.getElementById('alert-box');
            alertBox.textContent = message;
            alertBox.className = 'alert ' + (type === 'success' ? 'alert-success' : 'alert-error');
            alertBox.style.display = 'block';
        }
    </script>
</body>
</html>
"""

class WebRegistrationServer:
    def __init__(self, db_path: str = "wlo_server.db"):
        self.db = DatabaseManager(db_path)
        self.app = web.Application()
        self.setup_routes()

    def setup_routes(self):
        self.app.router.add_get('/', self.handle_index)
        self.app.router.add_post('/api/register', self.handle_register)

    async def handle_index(self, request):
        return web.Response(text=HTML_CONTENT, content_type='text/html', charset='utf-8')

    async def handle_register(self, request):
        try:
            data = await request.json()
            username = data.get('username', '').strip()
            password = data.get('password', '')

            if not username or not password:
                return web.json_response({"status": "error", "message": "Kullanıcı adı ve şifre gereklidir."}, status=400)

            if len(username) < 3 or len(username) > 15:
                return web.json_response({"status": "error", "message": "Kullanıcı adı 3-15 karakter arasında olmalıdır."}, status=400)

            if len(password) < 4 or len(password) > 20:
                return web.json_response({"status": "error", "message": "Şifre 4-20 karakter arasında olmalıdır."}, status=400)

            # Register user
            user_id, error = self.db.register_user(username, password)
            if error:
                return web.json_response({"status": "error", "message": "Kullanıcı adı zaten kullanımda veya geçersiz."}, status=400)

            logger.info(f"New user registered successfully: {username}")
            return web.json_response({"status": "success", "message": "Kayıt başarılı."})

        except Exception as e:
            logger.error(f"Error during registration: {e}")
            return web.json_response({"status": "error", "message": "Sistemsel bir hata oluştu."}, status=500)

    async def start(self, host="0.0.0.0", port=8081):
        runner = web.AppRunner(self.app, access_log=None)
        await runner.setup()
        site = web.TCPSite(runner, host, port)
        await site.start()
        logger.info(f"Web Registration Panel successfully started on http://{host}:{port}")
