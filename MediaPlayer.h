#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class MediaPlayer : public QMainWindow
{
    Q_OBJECT

public:
    MediaPlayer(QWidget *parent = nullptr);

private slots:
    void openFile();
    void play();
    void pause();
    void stop();
    void toggleFullscreen();
    void onPositionChanged(qint64 position);
    void onDurationChanged(qint64 duration);
    void seek(int position);

private:
    void setupUI();
    
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QPushButton *openButton, *playButton, *pauseButton, *stopButton, *fullscreenButton;
    QSlider *progressSlider;
    QLabel *fileNameLabel, *timeLabel;
};

#endif