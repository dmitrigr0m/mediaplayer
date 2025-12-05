#include "MediaPlayer.h"
#include <QStyle>
#include <QTime>
#include <QFileInfo>

MediaPlayer::MediaPlayer(QWidget *parent) : QMainWindow(parent)
{
    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    player->setVideoOutput(videoWidget);
    
    setupUI();
    
    // Подключаем сигналы и слоты
    connect(openButton, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(playButton, SIGNAL(clicked()), this, SLOT(play()));
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(pause()));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    connect(fullscreenButton, SIGNAL(clicked()), this, SLOT(toggleFullscreen()));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64)));
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(onDurationChanged(qint64)));
    connect(progressSlider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
    
    playButton->setEnabled(false);
    pauseButton->setEnabled(false);
    stopButton->setEnabled(false);
}

void MediaPlayer::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    // Создаем кнопки
    openButton = new QPushButton("Открыть", this);
    playButton = new QPushButton("Воспроизведение", this);
    pauseButton = new QPushButton("Пауза", this);
    stopButton = new QPushButton("Стоп", this);
    fullscreenButton = new QPushButton("Полный экран", this);
    
    // Добавляем иконки
    openButton->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    pauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    fullscreenButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
    
    // Создаем другие элементы
    progressSlider = new QSlider(Qt::Horizontal, this);
    fileNameLabel = new QLabel("Файл не выбран", this);
    timeLabel = new QLabel("00:00 / 00:00", this);
    
    // Компоновка интерфейса
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(videoWidget);
    mainLayout->addWidget(fileNameLabel);
    mainLayout->addWidget(progressSlider);
    
    QHBoxLayout *controlLayout = new QHBoxLayout();
    controlLayout->addWidget(timeLabel);
    controlLayout->addStretch();
    controlLayout->addWidget(openButton);
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(pauseButton);
    controlLayout->addWidget(stopButton);
    controlLayout->addWidget(fullscreenButton);
    
    mainLayout->addLayout(controlLayout);
    
    setMinimumSize(800, 600);
    setWindowTitle("Мультимедиа Проигрыватель");
}

void MediaPlayer::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть медиа файл", "",
        "Медиа файлы (*.mp4 *.avi *.mkv *.mov *.wmv *.mp3 *.wav *.flac);;Все файлы (*)");
    
    if (!fileName.isEmpty()) {
        player->setMedia(QUrl::fromLocalFile(fileName));
        QFileInfo fileInfo(fileName);
        fileNameLabel->setText("Текущий файл: " + fileInfo.fileName());
        playButton->setEnabled(true);
    }
}

void MediaPlayer::play()
{
    player->play();
    playButton->setEnabled(false);
    pauseButton->setEnabled(true);
    stopButton->setEnabled(true);
}

void MediaPlayer::pause()
{
    player->pause();
    playButton->setEnabled(true);
    pauseButton->setEnabled(false);
}

void MediaPlayer::stop()
{
    player->stop();
    playButton->setEnabled(true);
    pauseButton->setEnabled(false);
    stopButton->setEnabled(false);
}

void MediaPlayer::toggleFullscreen()
{
    videoWidget->setFullScreen(!videoWidget->isFullScreen());
}

void MediaPlayer::onPositionChanged(qint64 position)
{
    if (!progressSlider->isSliderDown()) {
        progressSlider->setValue(position);
    }
    
    qint64 duration = player->duration();
    QTime currentTime = QTime(0,0,0,0).addMSecs(position);
    QTime totalTime = QTime(0,0,0,0).addMSecs(duration);
    
    QString format = duration > 3600000 ? "hh:mm:ss" : "mm:ss";
    timeLabel->setText(currentTime.toString(format) + " / " + totalTime.toString(format));
}

void MediaPlayer::onDurationChanged(qint64 duration)
{
    progressSlider->setRange(0, duration);
}

void MediaPlayer::seek(int position)
{
    player->setPosition(position);
}
