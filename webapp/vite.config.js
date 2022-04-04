import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import { viteSingleFile } from "vite-plugin-singlefile"

let userSettings = null;
try {
  userSettings = require('./settings');
} catch(error) {
  console.error('ACHTUNG Die settings.js Datei ist nicht korrekt gesetzt. Guck dir die settings.example.js Datei an.');
  process.exit();
}

// https://vitejs.dev/config/
export default defineConfig({
	plugins: [vue(), viteSingleFile()],
  build: {
		target: "esnext",
		assetsInlineLimit: 100000000,
		chunkSizeWarningLimit: 100000000,
		cssCodeSplit: false,
		brotliSize: false,
		rollupOptions: {
			inlineDynamicImports: true,
			output: {
				manualChunks: () => "everything.js",
			},
		},
    outDir: './../data',
	},
  server: {
    open: true,
    port: 8080,
    proxy: {
      '^/api': { target: userSettings.proxyserver, ws: true, changeOrigin: true },
    }
  }
})
