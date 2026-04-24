#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>
#include <QPainter>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QFont>
#include <cstdlib>
#include <ctime>

class MainWindow : public QMainWindow
{

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void toggleConnection();
    void updateTimer();
    void updatePing();

private:
    void setConnectingState();
    void setConnectedState();
    void setDisconnectedState();
    void paintEvent(QPaintEvent *event) override;

    QPushButton *m_connectButton;
    QLabel *m_statusText;
    QLabel *m_timeLabel;
    QLabel *m_countryLabel;
    QLabel *m_pingLabel;
    QPushButton *m_pingButton;

    QTimer *m_timer;
    QTimer *m_pingTimer;
    int m_seconds;
    bool m_isConnected;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_seconds(0)
    , m_isConnected(false)
{
    setWindowTitle("DuseVPN");
    setFixedSize(380, 580);

    m_connectButton = new QPushButton(this);
    m_connectButton->setFixedSize(120, 120);
    m_connectButton->setText("⏻");
    QFont font = m_connectButton->font();
    font.setPointSize(42);
    font.setBold(true);
    m_connectButton->setFont(font);
    m_connectButton->setCursor(Qt::PointingHandCursor);
    m_connectButton->setStyleSheet(
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 #ffffff, stop:1 #e0e0e0);"
        "   border-radius: 60px;"
        "   color: #000000;"
        "   border: none;"
        "   padding-bottom: 6px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 #e0e0e0, stop:1 #c0c0c0);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 #cccccc, stop:1 #bbbbbb);"
        "}"
        );

    m_statusText = new QLabel("ВЫКЛЮЧЕН", this);
    m_statusText->setAlignment(Qt::AlignCenter);
    m_statusText->setStyleSheet("font-size: 12px; font-weight: bold; color: #e74c3c; letter-spacing: 1px;");

    m_timeLabel = new QLabel("00:00:00", this);
    m_timeLabel->setAlignment(Qt::AlignCenter);
    m_timeLabel->setStyleSheet("font-size: 13px; color: #aaaaaa;");

    m_countryLabel = new QLabel("Япония", this);
    m_countryLabel->setAlignment(Qt::AlignCenter);
    m_countryLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #ffffff; margin-top: 20px;");

    m_pingButton = new QPushButton("Тест пинга", this);
    m_pingButton->setFixedSize(130, 35);
    m_pingButton->setCursor(Qt::PointingHandCursor);
    m_pingButton->setStyleSheet(
        "QPushButton {"
        "   background: rgba(255,255,255,0.1);"
        "   border: 1px solid #ffffff;"
        "   border-radius: 17px;"
        "   color: #ffffff;"
        "   font-size: 11px;"
        "}"
        "QPushButton:hover {"
        "   background: rgba(255,255,255,0.2);"
        "}"
        );

    m_pingLabel = new QLabel("Пинг: -- мс", this);
    m_pingLabel->setAlignment(Qt::AlignCenter);
    m_pingLabel->setStyleSheet("font-size: 11px; color: #aaaaaa;");

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addStretch(2);
    mainLayout->addWidget(m_connectButton, 0, Qt::AlignCenter);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(m_statusText);
    mainLayout->addSpacing(5);
    mainLayout->addWidget(m_timeLabel);
    mainLayout->addStretch(1);
    mainLayout->addWidget(m_countryLabel);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(m_pingButton, 0, Qt::AlignCenter);
    mainLayout->addSpacing(5);
    mainLayout->addWidget(m_pingLabel);
    mainLayout->addStretch(2);

    QWidget *central = new QWidget(this);
    central->setLayout(mainLayout);
    setCentralWidget(central);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::updateTimer);

    connect(m_connectButton, &QPushButton::clicked, this, &MainWindow::toggleConnection);
    connect(m_pingButton, &QPushButton::clicked, this, &MainWindow::updatePing);
}

MainWindow::~MainWindow() {}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    QLinearGradient bgGradient(0, 0, width(), height());
    bgGradient.setColorAt(0, QColor(20, 20, 20));
    bgGradient.setColorAt(1, QColor(10, 10, 10));
    painter.fillRect(rect(), bgGradient);

    painter.setBrush(Qt::NoBrush);
    painter.setOpacity(0.25);

    QRadialGradient sand1(width() * 0.7, height() * 0.2, 300);
    sand1.setColorAt(0, QColor(255, 255, 255, 40));
    sand1.setColorAt(1, QColor(255, 255, 255, 0));
    painter.fillRect(rect(), sand1);

    QRadialGradient sand2(width() * 0.2, height() * 0.8, 250);
    sand2.setColorAt(0, QColor(255, 255, 255, 35));
    sand2.setColorAt(1, QColor(255, 255, 255, 0));
    painter.fillRect(rect(), sand2);

    QRadialGradient sand3(width() * 0.5, height() * 0.5, 350);
    sand3.setColorAt(0, QColor(255, 255, 255, 30));
    sand3.setColorAt(1, QColor(255, 255, 255, 0));
    painter.fillRect(rect(), sand3);

    QRadialGradient sand4(width() * 0.9, height() * 0.6, 280);
    sand4.setColorAt(0, QColor(255, 255, 255, 35));
    sand4.setColorAt(1, QColor(255, 255, 255, 0));
    painter.fillRect(rect(), sand4);

    painter.setOpacity(1.0);
}

void MainWindow::toggleConnection()
{
    if (m_isConnected) {
        setDisconnectedState();
    } else {
        setConnectingState();
        QTimer::singleShot(2000, this, &MainWindow::setConnectedState);
    }
}

void MainWindow::setConnectingState()
{
    m_connectButton->setEnabled(false);
    m_statusText->setText("СОЕДИНЕНИЕ");
    m_statusText->setStyleSheet("font-size: 12px; font-weight: bold; color: #f39c12; letter-spacing: 1px;");
    m_timeLabel->setText("--:--:--");
}

void MainWindow::setConnectedState()
{
    m_isConnected = true;
    m_connectButton->setEnabled(true);
    m_connectButton->setStyleSheet(
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 #e0e0e0, stop:1 #c0c0c0);"
        "   border-radius: 60px;"
        "   color: #000000;"
        "   border: none;"
        "   padding-bottom: 6px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 #c0c0c0, stop:1 #a0a0a0);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 #bbbbbb, stop:1 #aaaaaa);"
        "}"
        );
    m_statusText->setText("ЗАЩИЩЕНО");
    m_statusText->setStyleSheet("font-size: 12px; font-weight: bold; color: #2ecc71; letter-spacing: 1px;");
    m_timer->start(1000);
}

void MainWindow::setDisconnectedState()
{
    m_isConnected = false;
    m_seconds = 0;
    m_timeLabel->setText("00:00:00");
    m_timer->stop();
    m_connectButton->setEnabled(true);
    m_connectButton->setStyleSheet(
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 #ffffff, stop:1 #e0e0e0);"
        "   border-radius: 60px;"
        "   color: #000000;"
        "   border: none;"
        "   padding-bottom: 6px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 #e0e0e0, stop:1 #c0c0c0);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "       stop:0 #cccccc, stop:1 #bbbbbb);"
        "}"
        );
    m_statusText->setText("ВЫКЛЮЧЕН");
    m_statusText->setStyleSheet("font-size: 12px; font-weight: bold; color: #e74c3c; letter-spacing: 1px;");
}

void MainWindow::updatePing()
{
    int randomPing = 50 + (rand() % 200);
    m_pingLabel->setText(QString("Пинг: %1 мс").arg(randomPing));
}

void MainWindow::updateTimer()
{
    m_seconds++;
    int hours = m_seconds / 3600;
    int minutes = (m_seconds % 3600) / 60;
    int secs = m_seconds % 60;
    m_timeLabel->setText(QString("%1:%2:%3")
                             .arg(hours, 2, 10, QChar('0'))
                             .arg(minutes, 2, 10, QChar('0'))
                             .arg(secs, 2, 10, QChar('0')));
}

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
