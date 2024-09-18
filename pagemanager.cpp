#include "PageManager.h"

PageManager::PageManager(ESP8266WebServer& server) : server(server) { }

void PageManager::handlePage(const String& page) {
    String content = getPageContent(page);
    if (!content.isEmpty()) {
        server.send(200, "text/html", content);
    } else {
        server.send(404, "text/plain", "404: Not Found");
    }
}

String PageManager::getPageContent(const String& page) {
    if (page == "loginsistema") {
        return R"(
            <!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Saluduino System Login</title>
  <style>
    @import "https://fonts.googleapis.com/css?family=Ubuntu:400,700italic|Cabin:400";

    /* Estilos Globales */
    * {
      box-sizing: border-box;
    }

    html {
      height: 100%;
      width: 100%;
    }

    body {
      margin: 0;
      padding: 0;
      height: 100%;
      width: 100%;
      background: linear-gradient(135deg, #6e6e6e, #4d4d4d);
      background-size: cover;
      font-size: 10px;
      text-align: center;
    }

    /* Logo */
    #logo {
      animation: logo-entry 4s ease-in;
      width: 500px;
      margin: 0 auto; /* Centra el logo horizontalmente */
      position: relative;
      z-index: 40;
      padding-top: 50px; /* Ajusta la posición vertical del logo */
    }

    h1 {
      animation: text-glow 2s ease-out infinite alternate;
      font-family: 'Ubuntu', sans-serif;
      color: #00a4a2;
      font-size: 48px;
      font-size: 4.8rem;
      font-weight: bold;
      position: relative;
      text-shadow: 0 0 10px #000, 0 0 20px #000, 0 0 30px #000, 0 0 40px #000, 0 0 50px #000, 0 0 60px #000, 0 0 70px #000;
    }

    /* Formulario de Login */
    .stark-login {
      margin: 0 auto;
      width: 500px;
      position: relative;
      z-index: 4;
      padding-top: 20px; /* Espacio entre el logo y el formulario */
    }

    .stark-login form {
      animation: form-entry 3s ease-in-out;
      background: linear-gradient(#333, #222);
      border: 6px solid #00a4a2;
      box-shadow: 0 0 15px #00fffd;
      border-radius: 5px;
      height: 220px;
      position: relative;
      transition: 1s all;
    }

    .stark-login form:hover {
      border: 6px solid #00fffd;
      box-shadow: 0 0 25px #00fffd;
      transition: 1s all;
    }

    .stark-login input {
      background: linear-gradient(#333, #222);
      border: 1px solid #444;
      border-radius: 5px;
      box-shadow: 0 2px 0 #000;
      color: #888;
      display: block;
      font-family: 'Cabin', helvetica, arial, sans-serif;
      font-size: 13px;
      height: 40px;
      margin: 20px auto 10px;
      padding: 0 10px;
      text-shadow: 0 -1px 0 #000;
      width: 100%; /* Asegura que los campos de entrada ocupen todo el ancho del formulario */
      max-width: 400px; /* Ajusta el ancho máximo del formulario */
    }

    .stark-login input:focus {
      animation: box-glow 1s ease-out infinite alternate;
      background: linear-gradient(#333933, #222922);
      border-color: #00fffc;
      box-shadow: 0 0 5px rgba(0, 255, 253, .2), inset 0 0 5px rgba(0, 255, 253, .1), 0 2px 0 #000;
      color: #efe;
      outline: none;
    }

    .stark-login input:invalid {
      border: 2px solid red;
      box-shadow: 0 0 5px rgba(255, 0, 0, .2), inset 0 0 5px rgba(255, 0, 0, .1), 0 2px 0 #000;
    }

    .stark-login button {
      animation: input-entry 3s ease-in;
      background: linear-gradient(#333, #222);
      border: 1px solid #444;
      border-radius: 5px;
      box-shadow: 0 2px 0 #000;
      color: #fff;
      display: block;
      font-family: 'Cabin', helvetica, arial, sans-serif;
      font-size: 13px;
      height: 40px;
      line-height: 40px;
      margin: 20px auto;
      padding: 0;
      text-shadow: 0 -1px 0 #000;
      width: 100%; /* Asegura que el botón ocupe todo el ancho del formulario */
      max-width: 400px; /* Ajusta el ancho máximo del botón */
      transition: 1s all;
    }

    .stark-login button:hover,
    .stark-login button:focus {
      background: linear-gradient(#393939, #292929);
      color: #00fffc;
      outline: none;
      transition: 1s all;
    }

    .stark-login button:active {
      background: linear-gradient(#393939, #292929);
      box-shadow: 0 1px 0 #000, inset 1px 0 1px #222;
      top: 1px;
    }

    /* Círculo de Fondo */
    #circle1 {
      animation: circle1 4s linear infinite, circle-entry 6s ease-in-out;
      background: #000;
      border-radius: 50%;
      border: 10px solid #00a4a2;
      box-shadow: 0 0 0 2px black, 0 0 0 6px #00fffd;
      height: 500px;
      width: 500px;
      position: absolute;
      top: 50%;
      left: 50%;
      margin-top: -250px;
      margin-left: -250px;
      overflow: hidden;
      opacity: 0.4;
      z-index: -3;
    }

    #inner-cirlce1 {
      background: #000;
      border-radius: 50%;
      border: 36px solid #00fffd;
      height: 460px;
      width: 460px;
      margin: 10px;
    }

    /* Malla de Hexágonos */
    .hexagons {
      position: absolute;
      top: 0;
      left: 0;
      height: 100%;
      width: 100%;
      overflow: hidden;
      z-index: -2;
    }

    .hexagon {
      position: absolute;
      width: 100px;
      height: 100px;
      background-color: rgba(255, 255, 255, 0.1);
      clip-path: polygon(50% 0%, 100% 25%, 100% 75%, 50% 100%, 0% 75%, 0% 25%);
      border: 1px solid rgba(255, 255, 255, 0.3);
    }

    /* Animaciones */
    @keyframes logo-entry {
      0% { opacity: 0; }
      80% { opacity: 0; }
      100% { opacity: 1; }
    }

    @keyframes circle-entry {
      0% { opacity: 0; }
      20% { opacity: 0; }
      100% { opacity: 0.4; }
    }

    @keyframes input-entry {
      0% { opacity: 0; }
      90% { opacity: 0; }
      100% { opacity: 1; }
    }

    @keyframes form-entry {
      0% {
        height: 0;
        width: 0;
        opacity: 0;
        padding: 0;
      }
      20% {
        height: 0;
        border: 1px solid #00a4a2;
        width: 0;
        opacity: 0;
        padding: 0;
      }
      40% {
        width: 0;
        height: 220px;
        border: 6px solid #00a4a2;
        opacity: 1;
        padding: 0;
      }
      100% {
        height: 220px;
        width: 500px;
      }
    }

    @keyframes box-glow {
      0% {
        border-color: #00b8b6;
        box-shadow: 0 0 5px rgba(0, 255, 253, .2), inset 0 0 5px rgba(0, 255, 253, .1), 0 2px 0 #000;
      }
      100% {
        border-color: #00fffc;
        box-shadow: 0 0 10px rgba(0, 255, 253, .4), inset 0 0 20px rgba(0, 255, 253, .2), 0 2px 0 #000;
      }
    }

    @keyframes text-glow {
      0% {
        color: #00a4a2;
        text-shadow: 0 0 10px #000, 0 0 20px #000, 0 0 30px #000, 0 0 40px #000, 0 0 50px #000, 0 0 60px #000, 0 0 70px #000;
      }
      100% {
        color: #00fffd;
        text-shadow: 0 0 10px #00fffd, 0 0 20px #00fffd, 0 0 30px #00fffd, 0 0 40px #00fffd, 0 0 50px #00fffd, 0 0 60px #00fffd, 0 0 70px #00fffd;
      }
    }

    /* Posiciona los hexágonos aleatoriamente */
    .hexagon:nth-child(1) { top: 10%; left: 10%; }
    .hexagon:nth-child(2) { top: 20%; left: 20%; }
    .hexagon:nth-child(3) { top: 30%; left: 30%; }
    .hexagon:nth-child(4) { top: 40%; left: 40%; }
    .hexagon:nth-child(5) { top: 50%; left: 50%; }
    .hexagon:nth-child(6) { top: 60%; left: 60%; }
    .hexagon:nth-child(7) { top: 70%; left: 70%; }
    .hexagon:nth-child(8) { top: 80%; left: 80%; }
    .hexagon:nth-child(9) { top: 90%; left: 90%; }
  </style>
</head>
<body>
  <div id="logo">
    <h1>SerraIOT Systems</h1>
  </div>

  <div class="stark-login">
    <form action="/login" method="post">
      <input type="text" name="username" placeholder="Usuario" required>
      <input type="password" name="password" placeholder="Contraseña" required>
      <button type="submit">Entrar</button>
    </form>
  </div>

  <div id="circle1">
    <div id="inner-cirlce1"></div>
  </div>

  <div class="hexagons">
    <!-- Añade más hexágonos si es necesario -->
    <div class="hexagon"></div>
    <div class="hexagon"></div>
    <div class="hexagon"></div>
    <div class="hexagon"></div>
    <div class="hexagon"></div>
    <div class="hexagon"></div>
    <div class="hexagon"></div>
    <div class="hexagon"></div>
    <div class="hexagon"></div>
  </div>
</body>
</html>
        )";
    }
    if (page == "index") {
        return R"(
            <!DOCTYPE HTML>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Inicio - Saluduino</title>
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/plugins/fontawesome-free/css/all.min.css">
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/dist/css/adminlte.min.css">
</head>
<body class="hold-transition sidebar-mini">
  <div class="wrapper">
    <!-- Header and Sidebar -->
    <header class="main-header">
      <nav class="navbar navbar-expand navbar-dark">
        <ul class="navbar-nav">
          <li class="nav-item">
            <a class="nav-link" href="#"><i class="fas fa-bars"></i></a>
          </li>
          <li class="nav-item d-none d-sm-inline-block">
            <a href="/" class="nav-link">Inicio</a>
          </li>
        </ul>
      </nav>
    </header>
    <aside class="main-sidebar elevation-4">
      <a href="/" class="brand-link">
        <span class="brand-text font-weight-light">Saluduino</span>
      </a>
      <div class="sidebar">
        <nav class="mt-2">
          <ul class="nav nav-pills nav-sidebar flex-column" data-widget="treeview" role="menu" data-accordion="false">
            <li class="nav-item">
              <a href="/agregar-paciente" class="nav-link">
                <i class="nav-icon fas fa-user-plus"></i>
                <p>Agregar Paciente</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/quitar-paciente" class="nav-link">
                <i class="nav-icon fas fa-user-minus"></i>
                <p>Quitar Paciente</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/lista-pacientes" class="nav-link">
                <i class="nav-icon fas fa-list"></i>
                <p>Lista de Pacientes</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/hub-enfermero" class="nav-link">
                <i class="nav-icon fas fa-clinic-medical"></i>
                <p>Hub Enfermero</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/opciones-avanzadas" class="nav-link">
                <i class="nav-icon fas fa-cogs"></i>
                <p>Opciones Avanzadas</p>
              </a>
            </li>
          </ul>
        </nav>
      </div>
    </aside>
    <div class="content-wrapper">
      <div class="content-header">
        <div class="container-fluid">
          <h1 class="m-0 text-dark">Bienvenido a Saluduino</h1>
        </div>
      </div>
      <div class="content">
        <div class="container-fluid">
          <div class="row">
            <div class="col-md-6">
              <div class="info-box">
                <span class="info-box-icon bg-info elevation-1"><i class="fas fa-user-plus"></i></span>
                <div class="info-box-content">
                  <span class="info-box-text">Agregar Paciente</span>
                  <span class="info-box-number">
                    Agrega nuevos pacientes al sistema.
                  </span>
                </div>
              </div>
            </div>
            <div class="col-md-6">
              <div class="info-box">
                <span class="info-box-icon bg-warning elevation-1"><i class="fas fa-user-minus"></i></span>
                <div class="info-box-content">
                  <span class="info-box-text">Quitar Paciente</span>
                  <span class="info-box-number">
                    Elimina pacientes del sistema.
                  </span>
                </div>
              </div>
            </div>
            <div class="col-md-6">
              <div class="info-box">
                <span class="info-box-icon bg-success elevation-1"><i class="fas fa-list"></i></span>
                <div class="info-box-content">
                  <span class="info-box-text">Lista de Pacientes</span>
                  <span class="info-box-number">
                    Consulta la lista completa de pacientes.
                  </span>
                </div>
              </div>
            </div>
            <div class="col-md-6">
              <div class="info-box">
                <span class="info-box-icon bg-danger elevation-1"><i class="fas fa-clinic-medical"></i></span>
                <div class="info-box-content">
                  <span class="info-box-text">Hub Enfermero</span>
                  <span class="info-box-number">
                    Accede a las funciones de gestión de pacientes.
                  </span>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
    <footer class="main-footer">
      <strong>Saluduino - Sistema de Monitoreo &copy; 2024</strong>
    </footer>
  </div>
  <script src="https://adminlte.io/themes/v3/plugins/jquery/jquery.min.js"></script>
  <script src="https://adminlte.io/themes/v3/plugins/bootstrap/js/bootstrap.bundle.min.js"></script>
  <script src="https://adminlte.io/themes/v3/dist/js/adminlte.min.js"></script>
</body>
</html>
        )";
    }
    if (page == "lista-pacientes") {
        return R"(
            <!DOCTYPE HTML>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Lista de Pacientes - Saluduino</title>
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/plugins/fontawesome-free/css/all.min.css">
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/dist/css/adminlte.min.css">
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/plugins/datatables-bs4/css/dataTables.bootstrap4.min.css">
</head>
<body class="hold-transition sidebar-mini">
  <div class="wrapper">
    <!-- Header and Sidebar -->
    <header class="main-header">
      <nav class="navbar navbar-expand navbar-dark">
        <ul class="navbar-nav">
          <li class="nav-item">
            <a class="nav-link" href="#"><i class="fas fa-bars"></i></a>
          </li>
          <li class="nav-item d-none d-sm-inline-block">
            <a href="/" class="nav-link">Inicio</a>
          </li>
        </ul>
      </nav>
    </header>
    <aside class="main-sidebar elevation-4">
      <a href="/" class="brand-link">
        <span class="brand-text font-weight-light">Saluduino</span>
      </a>
      <div class="sidebar">
        <nav class="mt-2">
          <ul class="nav nav-pills nav-sidebar flex-column" data-widget="treeview" role="menu" data-accordion="false">
            <li class="nav-item">
              <a href="/agregar-paciente" class="nav-link">
                <i class="nav-icon fas fa-user-plus"></i>
                <p>Agregar Paciente</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/quitar-paciente" class="nav-link">
                <i class="nav-icon fas fa-user-minus"></i>
                <p>Quitar Paciente</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/lista-pacientes" class="nav-link active">
                <i class="nav-icon fas fa-list"></i>
                <p>Lista de Pacientes</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/hub-enfermero" class="nav-link">
                <i class="nav-icon fas fa-clinic-medical"></i>
                <p>Hub Enfermero</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/opciones-avanzadas" class="nav-link">
                <i class="nav-icon fas fa-cogs"></i>
                <p>Opciones Avanzadas</p>
              </a>
            </li>
          </ul>
        </nav>
      </div>
    </aside>
    <div class="content-wrapper">
      <div class="content-header">
        <div class="container-fluid">
          <h1 class="m-0 text-dark">Lista de Pacientes</h1>
        </div>
      </div>
      <div class="content">
        <div class="container-fluid">
          <table id="pacientes" class="table table-bordered table-hover">
            <thead>
              <tr>
                <th>Nombre</th>
                <th>DNI</th>
                <th>Fecha de Nacimiento</th>
                <th>Teléfono</th>
                <th>Acciones</th>
              </tr>
            </thead>
            <tbody>
              <!-- Aquí se llenarán los datos de pacientes -->
            </tbody>
          </table>
        </div>
      </div>
    </div>
    <footer class="main-footer">
      <strong>Saluduino - Sistema de Monitoreo &copy; 2024</strong>
    </footer>
  </div>
  <script src="https://adminlte.io/themes/v3/plugins/jquery/jquery.min.js"></script>
  <script src="https://adminlte.io/themes/v3/plugins/bootstrap/js/bootstrap.bundle.min.js"></script>
  <script src="https://adminlte.io/themes/v3/plugins/datatables/jquery.dataTables.min.js"></script>
  <script src="https://adminlte.io/themes/v3/plugins/datatables-bs4/js/dataTables.bootstrap4.min.js"></script>
  <script src="https://adminlte.io/themes/v3/dist/js/adminlte.min.js"></script>
  <script>
    $(function () {
      $("#pacientes").DataTable();
    });
  </script>
</body>
</html>
        )";
    }
    if (page == "agregar-paciente") {
        return R"(
            <!DOCTYPE HTML>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Agregar Paciente - Saluduino</title>
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/plugins/fontawesome-free/css/all.min.css">
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/dist/css/adminlte.min.css">
</head>
<body class="hold-transition sidebar-mini">
  <div class="wrapper">
    <!-- Header and Sidebar -->
    <header class="main-header">
      <nav class="navbar navbar-expand navbar-dark">
        <ul class="navbar-nav">
          <li class="nav-item">
            <a class="nav-link" href="#"><i class="fas fa-bars"></i></a>
          </li>
          <li class="nav-item d-none d-sm-inline-block">
            <a href="/" class="nav-link">Inicio</a>
          </li>
        </ul>
      </nav>
    </header>
    <aside class="main-sidebar elevation-4">
      <a href="/" class="brand-link">
        <span class="brand-text font-weight-light">Saluduino</span>
      </a>
      <div class="sidebar">
        <nav class="mt-2">
          <ul class="nav nav-pills nav-sidebar flex-column" data-widget="treeview" role="menu" data-accordion="false">
            <li class="nav-item">
              <a href="/agregar-paciente" class="nav-link active">
                <i class="nav-icon fas fa-user-plus"></i>
                <p>Agregar Paciente</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/quitar-paciente" class="nav-link">
                <i class="nav-icon fas fa-user-minus"></i>
                <p>Quitar Paciente</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/lista-pacientes" class="nav-link">
                <i class="nav-icon fas fa-list"></i>
                <p>Lista de Pacientes</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/hub-enfermero" class="nav-link">
                <i class="nav-icon fas fa-clinic-medical"></i>
                <p>Hub Enfermero</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/opciones-avanzadas" class="nav-link">
                <i class="nav-icon fas fa-cogs"></i>
                <p>Opciones Avanzadas</p>
              </a>
            </li>
          </ul>
        </nav>
      </div>
    </aside>
    <div class="content-wrapper">
      <div class="content-header">
        <div class="container-fluid">
          <h1 class="m-0 text-dark">Agregar Paciente</h1>
        </div>
      </div>
      <div class="content">
        <div class="container-fluid">
          <form>
            <div class="form-group">
              <label for="nombre_paciente">Nombre del Paciente</label>
              <input type="text" class="form-control" id="nombre_paciente" placeholder="Ingrese el nombre del paciente">
            </div>
            <div class="form-group">
              <label for="dni_paciente">DNI del Paciente</label>
              <input type="text" class="form-control" id="dni_paciente" placeholder="Ingrese el DNI del paciente">
            </div>
            <div class="form-group">
              <label for="fecha_nacimiento">Fecha de Nacimiento</label>
              <input type="date" class="form-control" id="fecha_nacimiento">
            </div>
            <div class="form-group">
              <label for="telefono_paciente">Teléfono de Contacto</label>
              <input type="text" class="form-control" id="telefono_paciente" placeholder="Ingrese el teléfono de contacto">
            </div>
            <button type="submit" class="btn btn-primary">Agregar Paciente</button>
          </form>
        </div>
      </div>
    </div>
    <footer class="main-footer">
      <strong>Saluduino - Sistema de Monitoreo &copy; 2024</strong>
    </footer>
  </div>
  <script src="https://adminlte.io/themes/v3/plugins/jquery/jquery.min.js"></script>
  <script src="https://adminlte.io/themes/v3/plugins/bootstrap/js/bootstrap.bundle.min.js"></script>
  <script src="https://adminlte.io/themes/v3/dist/js/adminlte.min.js"></script>
</body>
</html>
        )";
    }
    if (page == "quitar-paciente") {
        return R"(
            <!DOCTYPE HTML>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Quitar Paciente - Saluduino</title>
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/plugins/fontawesome-free/css/all.min.css">
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/dist/css/adminlte.min.css">
</head>
<body class="hold-transition sidebar-mini">
  <div class="wrapper">
    <!-- Header and Sidebar -->
    <header class="main-header">
      <nav class="navbar navbar-expand navbar-dark">
        <ul class="navbar-nav">
          <li class="nav-item">
            <a class="nav-link" href="#"><i class="fas fa-bars"></i></a>
          </li>
          <li class="nav-item d-none d-sm-inline-block">
            <a href="/" class="nav-link">Inicio</a>
          </li>
        </ul>
      </nav>
    </header>
    <aside class="main-sidebar elevation-4">
      <a href="/" class="brand-link">
        <span class="brand-text font-weight-light">Saluduino</span>
      </a>
      <div class="sidebar">
        <nav class="mt-2">
          <ul class="nav nav-pills nav-sidebar flex-column" data-widget="treeview" role="menu" data-accordion="false">
            <li class="nav-item">
              <a href="/agregar-paciente" class="nav-link">
                <i class="nav-icon fas fa-user-plus"></i>
                <p>Agregar Paciente</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/quitar-paciente" class="nav-link active">
                <i class="nav-icon fas fa-user-minus"></i>
                <p>Quitar Paciente</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/lista-pacientes" class="nav-link">
                <i class="nav-icon fas fa-list"></i>
                <p>Lista de Pacientes</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/hub-enfermero" class="nav-link">
                <i class="nav-icon fas fa-clinic-medical"></i>
                <p>Hub Enfermero</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/opciones-avanzadas" class="nav-link">
                <i class="nav-icon fas fa-cogs"></i>
                <p>Opciones Avanzadas</p>
              </a>
            </li>
          </ul>
        </nav>
      </div>
    </aside>
    <div class="content-wrapper">
      <div class="content-header">
        <div class="container-fluid">
          <h1 class="m-0 text-dark">Quitar Paciente</h1>
        </div>
      </div>
      <div class="content">
        <div class="container-fluid">
          <form>
            <div class="form-group">
              <label for="dni_paciente">DNI del Paciente</label>
              <input type="text" class="form-control" id="dni_paciente" placeholder="Ingrese el DNI del paciente">
            </div>
            <button type="submit" class="btn btn-danger">Quitar Paciente</button>
          </form>
        </div>
      </div>
    </div>
    <footer class="main-footer">
      <strong>Saluduino - Sistema de Monitoreo &copy; 2024</strong>
    </footer>
  </div>
  <script src="https://adminlte.io/themes/v3/plugins/jquery/jquery.min.js"></script>
  <script src="https://adminlte.io/themes/v3/plugins/bootstrap/js/bootstrap.bundle.min.js"></script>
  <script src="https://adminlte.io/themes/v3/dist/js/adminlte.min.js"></script>
</body>
</html>
        )";
    }
    if (page == "opciones-avanzadas") {
        return R"(
            <!DOCTYPE HTML>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Opciones Avanzadas - Saluduino</title>
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/plugins/fontawesome-free/css/all.min.css">
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/dist/css/adminlte.min.css">
</head>
<body class="hold-transition sidebar-mini">
  <div class="wrapper">
    <!-- Header and Sidebar -->
    <header class="main-header">
      <nav class="navbar navbar-expand navbar-dark">
        <ul class="navbar-nav">
          <li class="nav-item">
            <a class="nav-link" href="#"><i class="fas fa-bars"></i></a>
          </li>
          <li class="nav-item d-none d-sm-inline-block">
            <a href="/" class="nav-link">Inicio</a>
          </li>
        </ul>
      </nav>
    </header>
    <aside class="main-sidebar elevation-4">
      <a href="/" class="brand-link">
        <span class="brand-text font-weight-light">Saluduino</span>
      </a>
      <div class="sidebar">
        <nav class="mt-2">
          <ul class="nav nav-pills nav-sidebar flex-column" data-widget="treeview" role="menu" data-accordion="false">
            <li class="nav-item">
              <a href="/agregar-paciente" class="nav-link">
                <i class="nav-icon fas fa-user-plus"></i>
                <p>Agregar Paciente</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/quitar-paciente" class="nav-link">
                <i class="nav-icon fas fa-user-minus"></i>
                <p>Quitar Paciente</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/lista-pacientes" class="nav-link">
                <i class="nav-icon fas fa-list"></i>
                <p>Lista de Pacientes</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/hub-enfermero" class="nav-link">
                <i class="nav-icon fas fa-clinic-medical"></i>
                <p>Hub Enfermero</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/opciones-avanzadas" class="nav-link active">
                <i class="nav-icon fas fa-cogs"></i>
                <p>Opciones Avanzadas</p>
              </a>
            </li>
          </ul>
        </nav>
      </div>
    </aside>
    <div class="content-wrapper">
      <div class="content-header">
        <div class="container-fluid">
          <h1 class="m-0 text-dark">Opciones Avanzadas</h1>
        </div>
      </div>
      <div class="content">
        <div class="container-fluid">
          <h2>Gestión de Dispositivos</h2>
          <form>
            <div class="form-group">
              <label for="ip_dispositivo">IP del Dispositivo</label>
              <input type="text" class="form-control" id="ip_dispositivo" placeholder="Ingrese la IP del dispositivo">
            </div>
            <button type="submit" class="btn btn-primary">Agregar Dispositivo</button>
          </form>
          <hr>
          <h2>Configuraciones del Sistema</h2>
          <form>
            <div class="form-group">
              <label for="parametro_configuracion">Parámetro de Configuración</label>
              <input type="text" class="form-control" id="parametro_configuracion" placeholder="Ingrese el parámetro">
            </div>
            <button type="submit" class="btn btn-primary">Actualizar Configuración</button>
          </form>
        </div>
      </div>
    </div>
    <footer class="main-footer">
      <strong>Saluduino - Sistema de Monitoreo &copy; 2024</strong>
    </footer>
  </div>
  <script src="https://adminlte.io/themes/v3/plugins/jquery/jquery.min.js"></script>
  <script src="https://adminlte.io/themes/v3/plugins/bootstrap/js/bootstrap.bundle.min.js"></script>
  <script src="https://adminlte.io/themes/v3/dist/js/adminlte.min.js"></script>
</body>
</html>
        )";
    }
    if (page == "hub-enfermero") {
        return R"(
         <!DOCTYPE HTML>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Generar Reporte - Saluduino</title>
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/plugins/fontawesome-free/css/all.min.css">
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/dist/css/adminlte.min.css">
</head>
<body class="hold-transition sidebar-mini">
  <div class="wrapper">
    <!-- Header and Sidebar -->
    <header class="main-header">
      <nav class="navbar navbar-expand navbar-dark">
        <ul class="navbar-nav">
          <li class="nav-item">
            <a class="nav-link" href="#"><i class="fas fa-bars"></i></a>
          </li>
          <li class="nav-item d-none d-sm-inline-block">
            <a href="/" class="nav-link">Inicio</a>
          </li>
        </ul>
      </nav>
    </header>
    <aside class="main-sidebar elevation-4">
      <a href="/" class="brand-link">
        <span class="brand-text font-weight-light">Saluduino</span>
      </a>
      <div class="sidebar">
        <nav class="mt-2">
          <ul class="nav nav-pills nav-sidebar flex-column" data-widget="treeview" role="menu" data-accordion="false">
            <li class="nav-item">
              <a href="/agregar-paciente" class="nav-link">
                <i class="nav-icon fas fa-user-plus"></i>
                <p>Agregar Paciente</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/quitar-paciente" class="nav-link">
                <i class="nav-icon fas fa-user-minus"></i>
                <p>Quitar Paciente</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/lista-pacientes" class="nav-link">
                <i class="nav-icon fas fa-list"></i>
                <p>Lista de Pacientes</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/hub-enfermero" class="nav-link">
                <i class="nav-icon fas fa-clinic-medical"></i>
                <p>Hub Enfermero</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/opciones-avanzadas" class="nav-link">
                <i class="nav-icon fas fa-cogs"></i>
                <p>Opciones Avanzadas</p>
              </a>
            </li>
          </ul>
        </nav>
      </div>
    </aside>
    <div class="content-wrapper">
      <div class="content-header">
        <div class="container-fluid">
          <h1 class="m-0 text-dark">Generar Reporte</h1>
        </div>
      </div>
      <div class="content">
        <div class="container-fluid">
          <h2>Formulario de Reporte</h2>
          <form id="formGenerarReporte">
            <div class="form-group">
              <label for="inputFechaReporte">Fecha del Reporte</label>
              <input type="date" class="form-control" id="inputFechaReporte">
            </div>
            <div class="form-group">
              <label for="inputHoraReporte">Hora del Reporte</label>
              <input type="time" class="form-control" id="inputHoraReporte">
            </div>
            <div class="form-group">
              <label for="inputPaciente">Paciente</label>
              <input type="text" class="form-control" id="inputPaciente">
            </div>
            <div class="form-group">
              <label for="inputTemperatura">Temperatura (°C)</label>
              <input type="number" class="form-control" id="inputTemperatura">
            </div>
            <div class="form-group">
              <label for="inputOxigenacion">Oxigenación (%)</label>
              <input type="number" class="form-control" id="inputOxigenacion">
            </div>
            <div class="form-group">
              <label for="inputObservaciones">Observaciones</label>
              <textarea class="form-control" id="inputObservaciones"></textarea>
            </div>
            <div class="form-group">
              <label for="inputEnfermero">Enfermero</label>
              <input type="text" class="form-control" id="inputEnfermero">
            </div>
            <button type="submit" class="btn btn-primary">Generar PDF</button>
          </form>
        </div>
      </div>
    </div>
    <footer class="main-footer">
      <strong>Saluduino - Sistema de Monitoreo &copy; 2024</strong>
    </footer>
  </div>
  <!-- jQuery y jsPDF -->
  <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/jspdf/2.3.1/jspdf.umd.min.js"></script>
  <script>
    $(document).ready(function () {
      $('#formGenerarReporte').on('submit', function (e) {
        e.preventDefault();
        
        const { jsPDF } = window.jspdf;
        const doc = new jsPDF();
        
        const fecha = $('#inputFechaReporte').val();
        const hora = $('#inputHoraReporte').val();
        const paciente = $('#inputPaciente').val();
        const temperatura = $('#inputTemperatura').val();
        const oxigenacion = $('#inputOxigenacion').val();
        const observaciones = $('#inputObservaciones').val();
        const enfermero = $('#inputEnfermero').val();
        
        doc.text("Reporte del Paciente", 10, 10);
        doc.text(`Fecha: ${fecha}`, 10, 20);
        doc.text(`Hora: ${hora}`, 10, 30);
        doc.text(`Paciente: ${paciente}`, 10, 40);
        doc.text(`Temperatura: ${temperatura} °C`, 10, 50);
        doc.text(`Oxigenación: ${oxigenacion}%`, 10, 60);
        doc.text(`Observaciones: ${observaciones}`, 10, 70);
        doc.text(`Enfermero: ${enfermero}`, 10, 80);
        
        doc.save(`Reporte_${paciente}_${fecha}.pdf`);
      });
    });
  </script>
</body>
</html>
        )";
    }
    return "";
if (page == "agregar-paciente") {
<!DOCTYPE HTML>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Agregar Paciente - Saluduino</title>
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/plugins/fontawesome-free/css/all.min.css">
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/dist/css/adminlte.min.css">
</head>
<body class="hold-transition sidebar-mini">
  <div class="wrapper">
    <!-- Header and Sidebar -->
    <header class="main-header">
      <nav class="navbar navbar-expand navbar-dark">
        <ul class="navbar-nav">
          <li class="nav-item">
            <a class="nav-link" href="#"><i class="fas fa-bars"></i></a>
          </li>
          <li class="nav-item d-none d-sm-inline-block">
            <a href="/" class="nav-link">Inicio</a>
          </li>
        </ul>
      </nav>
    </header>
    <aside class="main-sidebar elevation-4">
      <a href="/" class="brand-link">
        <span class="brand-text font-weight-light">Saluduino</span>
      </a>
      <div class="sidebar">
        <nav class="mt-2">
          <ul class="nav nav-pills nav-sidebar flex-column" data-widget="treeview" role="menu" data-accordion="false">
            <li class="nav-item">
              <a href="/agregar-paciente" class="nav-link active">
                <i class="nav-icon fas fa-user-plus"></i>
                <p>Agregar Paciente</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/quitar-paciente" class="nav-link">
                <i class="nav-icon fas fa-user-minus"></i>
                <p>Quitar Paciente</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/lista-pacientes" class="nav-link">
                <i class="nav-icon fas fa-list"></i>
                <p>Lista de Pacientes</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/hub-enfermero" class="nav-link">
                <i class="nav-icon fas fa-clinic-medical"></i>
                <p>Hub Enfermero</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/opciones-avanzadas" class="nav-link">
                <i class="nav-icon fas fa-cogs"></i>
                <p>Opciones Avanzadas</p>
              </a>
            </li>
          </ul>
        </nav>
      </div>
    </aside>
    <div class="content-wrapper">
      <div class="content-header">
        <div class="container-fluid">
          <h1 class="m-0 text-dark">Agregar Paciente</h1>
        </div>
      </div>
      <div class="content">
        <div class="container-fluid">
          <form>
            <div class="form-group">
              <label for="nombre_paciente">Nombre del Paciente</label>
              <input type="text" class="form-control" id="nombre_paciente" placeholder="Ingrese el nombre del paciente">
            </div>
            <div class="form-group">
              <label for="dni_paciente">DNI del Paciente</label>
              <input type="text" class="form-control" id="dni_paciente" placeholder="Ingrese el DNI del paciente">
            </div>
            <div class="form-group">
              <label for="fecha_nacimiento">Fecha de Nacimiento</label>
              <input type="date" class="form-control" id="fecha_nacimiento">
            </div>
            <div class="form-group">
              <label for="telefono_paciente">Teléfono de Contacto</label>
              <input type="text" class="form-control" id="telefono_paciente" placeholder="Ingrese el teléfono de contacto">
            </div>
            <button type="submit" class="btn btn-primary">Agregar Paciente</button>
          </form>
        </div>
      </div>
    </div>
    <footer class="main-footer">
      <strong>Saluduino - Sistema de Monitoreo &copy; 2024</strong>
    </footer>
  </div>
  <script src="https://adminlte.io/themes/v3/plugins/jquery/jquery.min.js"></script>
  <script src="https://adminlte.io/themes/v3/plugins/bootstrap/js/bootstrap.bundle.min.js"></script>
  <script src="https://adminlte.io/themes/v3/dist/js/adminlte.min.js"></script>
</body>
</html>;
    }
if (page == "quitar-paciente") {
<!DOCTYPE HTML>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Quitar Paciente - Saluduino</title>
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/plugins/fontawesome-free/css/all.min.css">
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/dist/css/adminlte.min.css">
</head>
<body class="hold-transition sidebar-mini">
  <div class="wrapper">
    <!-- Header and Sidebar -->
    <header class="main-header">
      <nav class="navbar navbar-expand navbar-dark">
        <ul class="navbar-nav">
          <li class="nav-item">
            <a class="nav-link" href="#"><i class="fas fa-bars"></i></a>
          </li>
          <li class="nav-item d-none d-sm-inline-block">
            <a href="/" class="nav-link">Inicio</a>
          </li>
        </ul>
      </nav>
    </header>
    <aside class="main-sidebar elevation-4">
      <a href="/" class="brand-link">
        <span class="brand-text font-weight-light">Saluduino</span>
      </a>
      <div class="sidebar">
        <nav class="mt-2">
          <ul class="nav nav-pills nav-sidebar flex-column" data-widget="treeview" role="menu" data-accordion="false">
            <li class="nav-item">
              <a href="/agregar-paciente" class="nav-link">
                <i class="nav-icon fas fa-user-plus"></i>
                <p>Agregar Paciente</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/quitar-paciente" class="nav-link active">
                <i class="nav-icon fas fa-user-minus"></i>
                <p>Quitar Paciente</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/lista-pacientes" class="nav-link">
                <i class="nav-icon fas fa-list"></i>
                <p>Lista de Pacientes</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/hub-enfermero" class="nav-link">
                <i class="nav-icon fas fa-clinic-medical"></i>
                <p>Hub Enfermero</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/opciones-avanzadas" class="nav-link">
                <i class="nav-icon fas fa-cogs"></i>
                <p>Opciones Avanzadas</p>
              </a>
            </li>
          </ul>
        </nav>
      </div>
    </aside>
    <div class="content-wrapper">
      <div class="content-header">
        <div class="container-fluid">
          <h1 class="m-0 text-dark">Quitar Paciente</h1>
        </div>
      </div>
      <div class="content">
        <div class="container-fluid">
          <form>
            <div class="form-group">
              <label for="dni_paciente">DNI del Paciente</label>
              <input type="text" class="form-control" id="dni_paciente" placeholder="Ingrese el DNI del paciente">
            </div>
            <button type="submit" class="btn btn-danger">Quitar Paciente</button>
          </form>
        </div>
      </div>
    </div>
    <footer class="main-footer">
      <strong>Saluduino - Sistema de Monitoreo &copy; 2024</strong>
    </footer>
  </div>
  <script src="https://adminlte.io/themes/v3/plugins/jquery/jquery.min.js"></script>
  <script src="https://adminlte.io/themes/v3/plugins/bootstrap/js/bootstrap.bundle.min.js"></script>
  <script src="https://adminlte.io/themes/v3/dist/js/adminlte.min.js"></script>
</body>
</html>
    }
    if page("lista-paciente) }
        return "";
        <!DOCTYPE HTML>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Lista de Pacientes - Saluduino</title>
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/plugins/fontawesome-free/css/all.min.css">
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/dist/css/adminlte.min.css">
  <link rel="stylesheet" href="https://adminlte.io/themes/v3/plugins/datatables-bs4/css/dataTables.bootstrap4.min.css">
</head>
<body class="hold-transition sidebar-mini">
  <div class="wrapper">
    <!-- Header and Sidebar -->
    <header class="main-header">
      <nav class="navbar navbar-expand navbar-dark">
        <ul class="navbar-nav">
          <li class="nav-item">
            <a class="nav-link" href="#"><i class="fas fa-bars"></i></a>
          </li>
          <li class="nav-item d-none d-sm-inline-block">
            <a href="/" class="nav-link">Inicio</a>
          </li>
        </ul>
      </nav>
    </header>
    <aside class="main-sidebar elevation-4">
      <a href="/" class="brand-link">
        <span class="brand-text font-weight-light">Saluduino</span>
      </a>
      <div class="sidebar">
        <nav class="mt-2">
          <ul class="nav nav-pills nav-sidebar flex-column" data-widget="treeview" role="menu" data-accordion="false">
            <li class="nav-item">
              <a href="/agregar-paciente" class="nav-link">
                <i class="nav-icon fas fa-user-plus"></i>
                <p>Agregar Paciente</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/quitar-paciente" class="nav-link">
                <i class="nav-icon fas fa-user-minus"></i>
                <p>Quitar Paciente</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/lista-pacientes" class="nav-link active">
                <i class="nav-icon fas fa-list"></i>
                <p>Lista de Pacientes</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/hub-enfermero" class="nav-link">
                <i class="nav-icon fas fa-clinic-medical"></i>
                <p>Hub Enfermero</p>
              </a>
            </li>
            <li class="nav-item">
              <a href="/opciones-avanzadas" class="nav-link">
                <i class="nav-icon fas fa-cogs"></i>
                <p>Opciones Avanzadas</p>
              </a>
            </li>
          </ul>
        </nav>
      </div>
    </aside>
    <div class="content-wrapper">
      <div class="content-header">
        <div class="container-fluid">
          <h1 class="m-0 text-dark">Lista de Pacientes</h1>
        </div>
      </div>
      <div class="content">
        <div class="container-fluid">
          <table id="pacientes" class="table table-bordered table-hover">
            <thead>
              <tr>
                <th>Nombre</th>
                <th>DNI</th>
                <th>Fecha de Nacimiento</th>
                <th>Teléfono</th>
                <th>Acciones</th>
              </tr>
            </thead>
            <tbody>
              <!-- Aquí se llenarán los datos de pacientes -->
            </tbody>
          </table>
        </div>
      </div>
    </div>
    <footer class="main-footer">
      <strong>Saluduino - Sistema de Monitoreo &copy; 2024</strong>
    </footer>
  </div>
  <script src="https://adminlte.io/themes/v3/plugins/jquery/jquery.min.js"></script>
  <script src="https://adminlte.io/themes/v3/plugins/bootstrap/js/bootstrap.bundle.min.js"></script>
  <script src="https://adminlte.io/themes/v3/plugins/datatables/jquery.dataTables.min.js"></script>
  <script src="https://adminlte.io/themes/v3/plugins/datatables-bs4/js/dataTables.bootstrap4.min.js"></script>
  <script src="https://adminlte.io/themes/v3/dist/js/adminlte.min.js"></script>
  <script>
    $(function () {
      $("#pacientes").DataTable();
    });
  </script>
</body>
</html>
      }
      }
