// mainwindow.h
#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void openFile();
    void play();
    void pause();
    void stop();

private:
    void setupUI();
    void setupConnections();

    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QSlider *volumeSlider;
    QSlider *positionSlider;
};
