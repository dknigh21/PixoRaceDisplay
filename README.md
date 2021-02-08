# PixoRaceDisplay
NASCAR Race Monitor display for Pixo Pixel by Sean Hodgins

<img src="https://i.imgur.com/du4XqKu.png" style="width:400px; height:225px;"/>

<h3>Description</h3>
<p>Scrapes JSON data from NASCAR live feed, and updates PixoPixel display with number of current race leader.</p>

<h3>Equipment Used</h3>
<ul>
  <li><a href="https://www.kickstarter.com/projects/idlehandsdev/pixo-pixel-an-esp32-based-iot-rgb-display-for-make">Pixo Pixel by Sean Hodgins</a></li>
</ul>

<h3>Libraries Used</h3>
<ul>
  <li><a href="https://learn.adafruit.com/adafruit-dotstar-leds/dotstarmatrix-library">Adafruit DotStarMatrix</a></li>
  <li><a href="https://arduinojson.org/">ArduinoJSON</a></li>
</ul>

<h2>Image Viewer Excel File</h2>
<img src="https://i.imgur.com/EweB7ps.png" />
<p>The Pixo updates its images on screen using a 16x16 array for a total of 256 RGB values. Sean included a handy Python script to convert images down to this format, but I found that the final product sometimes had some artifacting and other issues. So I made a simple Excel file with a 16x16 grid so you can edit individual pixels directly, and it will write out the array needed and save it as "output.txt"<br><br>Also, if you have a text file with an already built image array, you can rename it "input.txt", place it in the same directory as the image viewer, and load it in to inspect/alter if need be.</p>

<h2>TODO</h2>
<ul>
  <li>Show Flags on display</li>
  <li>Scroll through top 5 positions</li>
  <li>Display other race info like track name, laps remaining, etc</li>
</ul>
