# OfflineLog

![Screenshot](https://github.com/virtuosonic/offlinelog/blob/master/screenshot.jpg)

A cross-platform desktop application for monitoring and logging internet connectivity status. OfflineLog continuously checks your internet connection and maintains a detailed log of online/offline periods with timestamps.

## Features

- 🔍 **Continuous Connectivity Monitoring**: Automatically monitors internet connectivity using REST API checks
- 📊 **Connection Event Logging**: Tracks and displays all connection changes with precise timestamps
- 🛡️ **False Positive Protection**: Uses an error counter to prevent false offline detections (requires 4 consecutive failures)
- 🎨 **Modern Qt Quick UI**: Clean and intuitive graphical interface built with QML
- ⏱️ **Timestamp Tracking**: Records start and end times for each connection period
- 🔄 **Real-time Status Updates**: Live status indicator showing current connection state


## Requirements

### Build Requirements

- **CMake** 3.16 or higher
- **Qt 6.8** or higher (with Qt Quick component)
- **C++17** compatible compiler
- **Qt Creator** (recommended) or any IDE with CMake support

### Runtime Requirements

- Windows, macOS, or Linux
- Internet connection (for connectivity testing)

## Installation

### Building from Source

1. **Clone the repository**
   ```bash
   git clone https://github.com/virtuosonic/offlinelog.git
   cd offlinelog
   ```

2. **Configure the build**
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

3. **Build the application**
   ```bash
   cmake --build .
   ```

   Or on Windows with Visual Studio:
   ```bash
   cmake --build . --config Release
   ```

4. **Run the application**
   ```bash
   ./appofflinelog  # Linux/macOS
   # or
   appofflinelog.exe  # Windows
   ```

### Using Qt Creator

1. Open Qt Creator
2. File → Open File or Project
3. Select `CMakeLists.txt` from the project root
4. Configure the project (select Qt 6.8 or higher)
5. Build and Run

## Usage

1. **Launch the application** - The app will immediately start monitoring your internet connection
2. **View status** - The top of the window shows your current connection status (Online/Offline/Verifying)
3. **Monitor logs** - The main list displays all connection events with start and end timestamps
4. **Automatic logging** - Connection changes are automatically logged as they occur

### How It Works

- The application periodically makes REST API calls to test connectivity
- Normal check interval: 10 seconds
- Error check interval: 2 seconds (when connection issues are detected)
- After 4 consecutive failures, the connection is marked as offline
- When connectivity is restored, the connection is immediately marked as online

## Project Structure

```
offlinelog/
├── CMakeLists.txt          # CMake build configuration
├── main.cpp                # Application entry point
├── Main.qml                # QML user interface
├── offlinelog.h/cpp        # Main application logic
├── logentrymodel.h/cpp     # List model for connection logs
├── errorcounter.h/cpp      # Error counting and state management
├── onlinetest.h/cpp        # REST API connectivity testing
└── ping.h/cpp              # Ping-based connectivity testing
```

## Development

### Code Style

- Follow Qt coding conventions
- Use 4 spaces for indentation (tabs converted to spaces)
- Class names use PascalCase
- Member variables prefixed with `m_`

### Adding Features

1. Create a feature branch: `git checkout -b feature/your-feature-name`
2. Make your changes
3. Test thoroughly
4. Commit your changes: `git commit -m "Add: description of feature"`
5. Push to the branch: `git push origin feature/your-feature-name`
6. Open a Pull Request

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes, please open an issue first to discuss what you would like to change.

### How to Contribute

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Reporting Bugs

If you find a bug, please open an issue with:
- A clear description of the problem
- Steps to reproduce the issue
- Expected vs actual behavior
- Your operating system and Qt version
- Any relevant error messages or logs

## License

This project is licensed under the MIT License 

## Acknowledgments

- Built with [Qt](https://www.qt.io/)
- Created by Gabriel Espinoza [virtuosonic](http://github.com/virtuosonic)

## Support

For support, please open an issue on GitHub or contact the maintainer.

## Changelog

### Version 1.0 (Current)
- Initial release
- Basic connectivity monitoring
- Connection event logging
- Qt Quick GUI
