// mainwindow.cpp
#include "mainwindow.h"
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , player(new QMediaPlayer(this))
    , videoWidget(new QVideoWidget(this))
{
    setupUI();
    setupConnections();

    player->setVideoOutput(videoWidget);
    setCentralWidget(videoWidget);
}

void MainWindow::setupUI() {
    // Создание кнопок
    playButton = new QPushButton("Play", this);
    pauseButton = new QPushButton("Pause", this);
    stopButton = new QPushButton("Stop", this);

    // Слайдеры
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50);

    positionSlider = new QSlider(Qt::Horizontal, this);

    // Панель инструментов
    QToolBar *toolbar = addToolBar("Controls");
    toolbar->addWidget(playButton);
    toolbar->addWidget(pauseButton);
    toolbar->addWidget(stopButton);
    toolbar->addWidget(new QLabel("Volume:", this));
    toolbar->addWidget(volumeSlider);
    toolbar->addWidget(positionSlider);
}

void MainWindow::setupConnections() {
    connect(playButton, &QPushButton::clicked, this, &MainWindow::play);
    connect(pauseButton, &QPushButton::clicked, this, &MainWindow::pause);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::stop);
    connect(volumeSlider, &QSlider::valueChanged, player, &QMediaPlayer::setVolume);
    connect(player, &QMediaPlayer::positionChanged, this, [this](qint64 pos){
        positionSlider->setValue(pos);
    });
    connect(player, &QMediaPlayer::durationChanged, this, [this](qint64 dur){
        positionSlider->setRange(0, dur);
    });
    connect(positionSlider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);
}

void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
        "Open Media File", "",
        "Media Files (*.mp3 *.mp4 *.avi *.mkv *.wav)");

    if (!fileName.isEmpty()) {
        player->setMedia(QUrl::fromLocalFile(fileName));
        play();
    }
}

void MainWindow::play() {
    player->play();
}

void MainWindow::pause() {
    player->pause();
}

void MainWindow::stop() {
    player->stop();
}
