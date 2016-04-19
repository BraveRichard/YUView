/*  YUView - YUV player with advanced analytics toolset
*   Copyright (C) 2015  Institut für Nachrichtentechnik
*                       RWTH Aachen University, GERMANY
*
*   YUView is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.
*
*   YUView is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with YUView.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PLAYLISTITEMYUVFILE_H
#define PLAYLISTITEMYUVFILE_H

#include "playlistItem.h"
#include "typedef.h"
#include "fileSource.h"
#include <QString>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QDir>
#include <QThread>
#include <QMutex>
#include "playlistItem.h"
#include "videoHandlerYUV.h"

// TODO: On windows this seems to be 4. Is it different on other platforms? 
// A QPixmap is handeled by the underlying window system so we cannot ask the pixmap.
#define PIXMAP_BYTESPERPIXEL 4

class playlistItemYUVFile :
  public playlistItem
{
  Q_OBJECT

public:
  playlistItemYUVFile(QString yuvFilePath, QSize frameSize=QSize(-1,-1), indexRange startEndFrame=indexRange(-1,-1), int sampling=-1, int frameRate=-1, QString sourcePixelFormat="");
  ~playlistItemYUVFile();

  // Overload from playlistItem. Save the yuv file item to playlist.
  virtual void savePlaylist(QDomElement &root, QDir playlistDir) Q_DECL_OVERRIDE;

  // Override from playlistItem. Return the info title and info list to be shown in the fileInfo groupBox.
  virtual QString getInfoTitel() Q_DECL_OVERRIDE { return "YUV File Info"; }
  virtual QList<infoItem> getInfoList() Q_DECL_OVERRIDE;

  virtual QString getPropertiesTitle() Q_DECL_OVERRIDE { return "YUV File Properties"; }

  // Create a new playlistItemYUVFile from the playlist file entry. Return NULL if parsing failed.
  static playlistItemYUVFile *newplaylistItemYUVFile(QDomElementYUV root, QString playlistFilePath);

  double startBuffering(int startFrame, int endFrame);
  void   bufferFrame(int frameIdx);

  // A YUV video file is indexed by frame
  virtual bool isIndexedByFrame() Q_DECL_OVERRIDE { return true; };

  // All the functions that we have to overload if we are indexed by frame
  virtual double getFrameRate() Q_DECL_OVERRIDE { return yuvVideo.getFrameRate(); }
  virtual QSize  getSize()      Q_DECL_OVERRIDE { return yuvVideo.getSize(); }
  virtual int    getSampling()  Q_DECL_OVERRIDE { return yuvVideo.getSampling(); }
  virtual indexRange getFrameIndexRange() { return yuvVideo.getFrameIndexRange(); }

  // A YUV file can be used in a difference
  virtual bool canBeUsedInDifference() Q_DECL_OVERRIDE { return true; }
  virtual videoHandler *getVideoHandler() Q_DECL_OVERRIDE { return &yuvVideo; }

  virtual ValuePairList getPixelValues(QPoint pixelPos) Q_DECL_OVERRIDE { return yuvVideo.getPixelValues(pixelPos); }

  // Draw
  virtual void drawItem(QPainter *painter, int frameIdx, double zoomFactor);

  // -- Caching
  // A YUV file can be cached
  virtual bool isCachable() Q_DECL_OVERRIDE { return true; }
  // Cache the given frame
  virtual void cacheFrame(int idx) Q_DECL_OVERRIDE { yuvVideo.cacheFrame(idx); }
  // Get a list of all cached frames (just the frame indices)
  virtual QList<int> getCachedFrames() Q_DECL_OVERRIDE { return yuvVideo.getCachedFrames(); }
  // How many bytes will caching one frame use (in bytes)?
  // For a YUV file we only cache the output pixmap so it is w*h*PIXMAP_BYTESPERPIXEL bytes. 
  virtual unsigned int getCachingFrameSize() Q_DECL_OVERRIDE { return getSize().width() * getSize().height() * PIXMAP_BYTESPERPIXEL; }

public slots:
  //virtual void removeFromCache(indexRange range) Q_DECL_OVERRIDE;

  // Load the YUV data for the given frame index from file. This slot is called by the videoHandlerYUV if the frame that is
  // requested to be drawn has not been loaded yet.
  virtual void loadYUVData(int frameIdx);

  // The videoHandlerYUV want's to know if the current frame range changed.
  virtual void slotUpdateFrameRange();

protected:

  // Try to get and set the format from file name. If after calling this function isFormatValid()
  // returns false then it failed.
  void setFormatFromFileName();
  
  // Override from playlistItemVideo. Load the given frame from file and convert it to pixmap.
  
  //virtual bool loadIntoCache(int frameIdx) Q_DECL_OVERRIDE;

  // Get the YUV values for the given pixel from the file. Overriden from playlistItemYuvSource
  //virtual void getPixelValue(QPoint pixelPos, unsigned int &Y, unsigned int &U, unsigned int &V) Q_DECL_OVERRIDE;

private:

  // Overload from playlistItem. Create a properties widget custom to the YUVFile
  // and set propertiesWidget to point to it.
  virtual void createPropertiesWidget() Q_DECL_OVERRIDE;

  virtual qint64 getNumberFrames();
  
  fileSource dataSource;

  QMutex mutex;

  videoHandlerYUV yuvVideo;

};

#endif