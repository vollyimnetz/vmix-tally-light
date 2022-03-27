
let userSettings = null;
try {
  userSettings = require('./settings');
} catch(error) {
  if(process.env.NODE_ENV === 'production') {
    userSettings = {
      proxyserver:'anything',//not used in production
    }
  } else {
    console.error('ACHTUNG Die settings.js Datei ist nicht korrekt gesetzt. Guck dir die settings.example.js Datei an.');
    process.exit()
  }
}

module.exports = {
  outputDir: '../data',

  //do only one file
  chainWebpack: config => { config.optimization.delete("splitChunks"); },
  css : { extract: false },
  productionSourceMap: false,


  devServer: {
    open: true,
    historyApiFallback: true,//show index on every route
    proxy: {
      //'^/api': { target: 'http://127.0.0.1:8000', ws: true, changeOrigin: true },
      '^/api': {
        target: userSettings.proxyserver,
        changeOrigin: true,
        ws: true,
        onProxyRes: proxyResponse => {//handle secure cookies
          if (proxyResponse.headers['set-cookie']) {
            const cookies = proxyResponse.headers['set-cookie'].map(cookie =>
              cookie.replace(/; secure/gi, '')
            );
            proxyResponse.headers['set-cookie'] = cookies;
          }
        }
      },
    }
  }
}